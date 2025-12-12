#pragma once
#include <unordered_map>
#include "dialogueNode.h"
#include "activeDialogue.h"
#include "textDB.h"
#include "renderer.h"  
#include "event.h"
 
class inputManager;
struct movedThisFrameEvent;
struct dialogueProposalEvent;
struct setUpDialogueBubbleEvent;
struct startDialogueEvent;
struct turnContext;

//ADD MOVEMENT EVENT TO UPDATE BUBBLE ORIENTATION
class dialogueManager {
public: 
    dialogueManager();
    ~dialogueManager();

   int findDialogueIndexByNodeId(int nodeId) const;

    void setDialogueNodesDatabase(int dbId);
    void setStringDatabase(int dbId);
    activeDialogue* startDialogue(int id);

    void tickDialogue();
    bool advanceDialogue(activeDialogue& dlg);
    void handleInput(inputManager& input);

    const std::vector<activeDialogue>& getActiveDialogues() const { return activeDialogues; }
  

    void processDialogueProposalEvent(turnContext& ctx, dialogueProposalEvent& e, eventPhase phase);
    void processSetUpDialogueBubbleEvent(turnContext& ctx, setUpDialogueBubbleEvent& e, eventPhase phase);
    void processStartDialogueEvent(turnContext& ctx, startDialogueEvent& e, eventPhase phase);
    void processMovedThisFrameEvent(turnContext& ctx, movedThisFrameEvent& e, eventPhase phase);
private: 
    std::unordered_map<int, dialogueNode> dialogueNodes;
    std::vector<activeDialogue> activeDialogues;
    textDatabase textDB;
};
