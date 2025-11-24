#pragma once
#include <unordered_map>
#include "dialogueNode.h"
#include "activeDialogue.h"
#include "textDB.h"
#include "renderer.h" 
#include "turnContext.h"

class dialogueManager {
public: 
    dialogueManager();
    ~dialogueManager();

    void setDialogueNodesDatabase(int dbId);
    void setStringDatabase(int dbId);
    activeDialogue* startDialogue(int id);
    void advanceDialogue(activeDialogue& dlg);

    const std::vector<activeDialogue>& getActiveDialogues() const { return activeDialogues; }

    void processEvent(turnContext& ctx, gameEvent& event);
    void executeEvent(turnContext& ctx, gameEvent& event);

private: 
    std::unordered_map<int, dialogueNode> dialogueNodes;
    std::vector<activeDialogue> activeDialogues;
    textDatabase textDB;
};
