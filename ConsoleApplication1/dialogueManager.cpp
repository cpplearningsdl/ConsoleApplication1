#pragma once
#include <windows.h>
#include <fstream>
#include "logManager.h"
#include "dialogueManager.h"
#include "dialogueEvents.h"
#include "dialogeEventHelperFunctions.h"
#include "movementEvents.h"
#include "event.h"
#include "textureManager.h" 
#include "json.hpp"
#include "turnContext.h"
#include "windowSettings.h"

dialogueManager::dialogueManager() {

}
dialogueManager::~dialogueManager() {
    dialogueNodes.clear();
    activeDialogues.clear();
    textDB.clear();
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


void dialogueManager::processDialogueProposalEvent(turnContext& ctx, dialogueProposalEvent& e, eventPhase phase) {
    if (phase == eventPhase::EXECUTE) {
        ctx.emitEvent<startDialogueEvent>(e.dialogueNode);
    }
}

void dialogueManager::processStartDialogueEvent(turnContext& ctx, startDialogueEvent& e, eventPhase phase) {
    if (phase == eventPhase::PROCESS) {
       activeDialogue* d = startDialogue(e.dialogueNode);
       e.entityId = d->entityId;
    }else { 
        for (auto& d : activeDialogues) {
            if (d.entityId == e.entityId) {
                setUpDialogueBubble(e.entityPos, ctx.cameraViewPos, d);
            }
        }
    }
}

 
void dialogueManager::processMovedThisFrameEvent(turnContext& ctx, movedThisFrameEvent& e, eventPhase phase) {
    if (!activeDialogues.empty()) {
        for (auto& d : activeDialogues) {
            auto it = dialogueNodes.find(d.nodeId);
            if (it == dialogueNodes.end()) continue;

            const auto& node = it->second;
            if (node.entityId != e.entityId) continue;
            d.textBubblePos = e.pos;
 
        }
    }
    else { return; }
}

void dialogueManager::processSetUpDialogueBubbleEvent(turnContext& ctx, setUpDialogueBubbleEvent& e, eventPhase phase) {
    if (phase == eventPhase::EXECUTE) {
        for (auto& d : activeDialogues) {
            if (d.entityId == e.entityId) {
                float w, h;
                screenQuadrant quad = getScreenQuadrant(e.entityPos, ctx.cameraViewPos, logicalW, logicalH);
                d.textBubblePos = getTextBubbleScreenPos(e.entityPos, ctx.cameraViewPos, logicalW, logicalH, quad);
                d.bubbleTextureKey = d.bubbleTextureKeyBase + getOrientedBubblesTextureKeySuffix(quad);
                d.bubbleTexture = textureManager::getInstance().getFrame(d.bubbleTextureKey);
                SDL_GetTextureSize(d.bubbleTexture, &w, &h);
                d.textBubbleSize.setSize(w, h);
                d.speakerLabel.updateTexture(d.speakerLabel.text);
                d.textLabel.updateTexture(d.textLabel.text);
                break;
            }
        }
    }
}


activeDialogue* dialogueManager::startDialogue(int id) {
    auto it = dialogueNodes.find(id);
    if (it == dialogueNodes.end())
        return nullptr;

    const auto& node = it->second;
    activeDialogue dlg;
    dlg.nodeId = id;
    dlg.entityId = node.entityId;
     
    dlg.bubbleTextureKeyBase = node.bubbleTextureKeyBase;
    dlg.bubbleTextureKey = "textBubble_fromLeft_0";


    // Speaker label
    dlg.speakerLabel.color = node.speakerFontColor;
    dlg.speakerLabel.posOffset = {10.0f, 10.0f };
    dlg.speakerLabel.text = textDB.get(node.speakerId); 
    //dlg.speakerLabel.updateTexture(dlg.speakerLabel.text); 

    // Text label
    dlg.textLabel.color = node.textFontColor;
    dlg.textLabel.posOffset = {10.0f, 40.0f };
    dlg.textLabel.text = textDB.get(node.textId);
    //dlg.textLabel.updateTexture(dlg.textLabel.text);
     
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
