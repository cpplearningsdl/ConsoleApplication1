#pragma once
#include <windows.h>
#include <fstream>
#include "logManager.h"
#include "dialogueManager.h"
#include "textureManager.h"
#include "overLoaded.h"
#include "json.hpp"
#include "turnContext.h"

dialogueManager::dialogueManager() {

}
dialogueManager::~dialogueManager() {
    dialogueNodes.clear();
    activeDialogues.clear();
    textDB.clear();
}
void dialogueManager::processEvent(turnContext& ctx, const gameEvent& event) {
    std::visit(overloaded{
        [&](const enteredTileEvent&) {}, // check renderable
        [&](const entityDiedEvent&) {}, // probably leaving dead entities on map
        [](auto&) {}
        }, event);

}
void dialogueManager::executeEvent(turnContext& ctx, const gameEvent& event) {
    std::visit(overloaded{
        [&](const enteredTileEvent&) {}, // check renderable
        [&](const entityDiedEvent&) {}, // probably leaving dead entities on map
        [](auto&) {}
        }, event);

}

void dialogueManager::setDialogueNodesDatabase(int dbId) {
    namespace fs = std::filesystem;
    nlohmann::ordered_json db;

    // Get the folder containing the executable
    char buffer[MAX_PATH];
    DWORD len = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    if (len == 0 || len == MAX_PATH) {
        logManager::logThis("Failed to get executable path");
        return;
    }
    fs::path exeFolder = fs::path(buffer).parent_path();
    fs::path filePath = exeFolder / "dialogues" / ("dialogueNodes" + std::to_string(dbId) + ".json");

    std::ifstream file(filePath);
    if (!file.is_open()) {
        logManager::logThis("Couldn't open dialogue file: ", filePath.string());
        logManager::logThis("Working dir: ", fs::current_path().string());
        return;
    }

    file >> db;
    std::vector<dialogueNode> list = db.get<std::vector<dialogueNode>>();
    dialogueNodes.clear();
    for (auto& n : list) {
        dialogueNodes.emplace(n.id, std::move(n));
    }
}
    
void dialogueManager::setStringDatabase(int dbId) {
    namespace fs = std::filesystem; 
    nlohmann::ordered_json db;

    // Get the folder containing the executable
    char buffer[MAX_PATH];
    DWORD len = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    if (len == 0 || len == MAX_PATH) {
        logManager::logThis("Failed to get executable path");
        return;
    }
    fs::path exeFolder = fs::path(buffer).parent_path(); 
    fs::path filePath = exeFolder / "dialogues" / ("stringDB" + std::to_string(dbId) + ".json");

    std::ifstream file(filePath);
    if (!file.is_open()) {
        logManager::logThis("Couldn't open dialogue file: ", filePath.string());
        logManager::logThis("Working dir: ", fs::current_path().string());
        return;
    }

    file >> db; 
    textDB = db.get<textDatabase>();
}


activeDialogue* dialogueManager::startDialogue(int id) {
    auto it = dialogueNodes.find(id);
    if (it == dialogueNodes.end())
        return nullptr;

    const auto& node = it->second;
    activeDialogue dlg;
    dlg.nodeId = id;
    dlg.bubbleTexture = textureManager::getInstance().getFrame(node.bubbleTextureKey);
    dlg.bubbleRect = { 100.0f, 100.0f, 300.0f, 150.0f }; 

    // Speaker label
    dlg.speakerLabel.color = { 255, 255, 0, 255 };
    dlg.speakerLabel.pos = { dlg.bubbleRect.x + 10.0f, dlg.bubbleRect.y + 10.0f };
    dlg.speakerLabel.text = textDB.get(node.speakerId); 
    dlg.speakerLabel.updateTexture(dlg.speakerLabel.text); 

    // Text label
    dlg.textLabel.color = { 255, 255, 255, 255 };
    dlg.textLabel.pos = { dlg.bubbleRect.x + 10.0f, dlg.bubbleRect.y + 40.0f };
    dlg.textLabel.text = textDB.get(node.textId);
    dlg.textLabel.updateTexture(dlg.textLabel.text); 

    activeDialogues.push_back(std::move(dlg));
    return &activeDialogues.back();
}


void dialogueManager::advanceDialogue(activeDialogue& dlg) {
    auto it = dialogueNodes.find(dlg.nodeId);
    if (it == dialogueNodes.end()) return;

    int nextId = it->second.nextId;
    if (nextId == -1) {
        dlg.visible = false;
        return;
    }

    dlg = *startDialogue(nextId);
}
