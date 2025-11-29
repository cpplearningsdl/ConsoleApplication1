#pragma once
#include <unordered_map>
#include "dialogueNode.h"
#include "activeDialogue.h"
#include "textDB.h"
#include "renderer.h"  
#include "dialogueEvents.h"

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
 


    void processDialogueProposal(turnContext& ctx, dialogueProposalEvent& ev);
    void executeDialogueProposal(turnContext& ctx, dialogueProposalEvent& ev);
    void processStartDialogue(turnContext& ctx, startDialogueEvent& ev);
    void executeStartDialogue(turnContext& ctx, startDialogueEvent& ev);

private: 
    std::unordered_map<int, dialogueNode> dialogueNodes;
    std::vector<activeDialogue> activeDialogues;
    textDatabase textDB;
};
