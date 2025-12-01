#pragma once
#include "event.h"
#include "path.h"
#include "dialogueManager.h"

class entity;
class movementManager;
class dialogueManager;
class renderManager;

//EMIT AN EVENT TO SET THE TEXT BUBBLE POS TO THE ENTITY POS//REMOVE THIS COMMENT FROM DIALOGUEMANAGER.CPP TOO

 //DIALOGUE PROPOSAL EVENT
struct dialogueProposalEvent : baseEvent {
    int dialogueNode; 

    dialogueProposalEvent(int node, bool approval) : dialogueNode(node) {}

    void dispatch(movementManager& m, dialogueManager& d, renderCacheManager& r, turnContext& ctx) override { 
        d.processDialogueProposalEvent(ctx, *this, phase);   // dialogue sees it 
    }
};

//START DIALOGUE EVENT
struct startDialogueEvent : baseEvent {
    int dialogueNode; 

    startDialogueEvent(int node, bool approval) : dialogueNode(node) {}

    void dispatch(movementManager& m, dialogueManager& d, renderCacheManager& r, turnContext& ctx) override {
        d.processStartDialogueEvent(ctx, *this, phase);   // dialogue sees it 
    }
}; 