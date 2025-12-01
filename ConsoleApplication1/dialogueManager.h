#pragma once
#include <unordered_map>
#include "dialogueNode.h"
#include "activeDialogue.h"
#include "textDB.h"
#include "renderer.h"  
#include "event.h"
 
struct movedThisFrameEvent;
struct dialogueProposalEvent;
struct startDialogueEvent;
struct turnContext;

class dialogueManager {
public: 
    dialogueManager();
    ~dialogueManager();

    void setDialogueNodesDatabase(int dbId);
    void setStringDatabase(int dbId);
    activeDialogue* startDialogue(int id);
    void advanceDialogue(activeDialogue& dlg);

    const std::vector<activeDialogue>& getActiveDialogues() const { return activeDialogues; }
  

    void processDialogueProposalEvent(turnContext& ctx, dialogueProposalEvent& e, eventPhase phase);
    void processStartDialogueEvent(turnContext& ctx, startDialogueEvent& e, eventPhase phase);
    void processMovedThisFrameEvent(turnContext& ctx, movedThisFrameEvent& e, eventPhase phase);
private: 
    std::unordered_map<int, dialogueNode> dialogueNodes;
    std::vector<activeDialogue> activeDialogues;
    textDatabase textDB;
};
