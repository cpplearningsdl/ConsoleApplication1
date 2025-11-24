#pragma once
#include <windows.h>
#include <fstream>
#include "logManager.h"
#include "dialogueManager.h"
#include "dialogeEventHelperFunctions.h"
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

void dialogueManager::processEvent(turnContext& ctx, gameEvent& event) {
    std::visit(overloaded{
        [&](enteredTileEvent&) {}, // check start dialogue
        [&](entityDiedEvent&) {}, 
        [&](dialogueProposalEvent&) {},
        [&](startDialogueEvent&) {},
        [](auto&) {}
        }, event);

}
void dialogueManager::executeEvent(turnContext& ctx, gameEvent& event) {
    std::visit(overloaded{
        [&](enteredTileEvent& e) {}, // check renderable
        [&](entityDiedEvent& e) {},
        [&](dialogueProposalEvent& e) {dialogueProposal(ctx, e); },
        [&](startDialogueEvent& e) {},
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
    float w, h;
    SDL_GetTextureSize(dlg.bubbleTexture, &w, &h);
    dlg.textBubbleSize.setSize(w, h);

    // Speaker label
    dlg.speakerLabel.color = dlg.speakerLabel.color;
    dlg.speakerLabel.posOffset = {10.0f, 10.0f };
    dlg.speakerLabel.text = textDB.get(node.speakerId); 
    dlg.speakerLabel.updateTexture(dlg.speakerLabel.text); 

    // Text label
    dlg.textLabel.color = dlg.textLabel.color;
    dlg.textLabel.posOffset = {10.0f, 40.0f };
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
