#pragma once
#include "event.h"
#include "path.h" 

class entity;
class entityManager;
class movementManager;
class dialogueManager;
class renderManager;

//EMIT AN EVENT TO SET THE TEXT BUBBLE POS TO THE ENTITY POS//REMOVE THIS COMMENT FROM DIALOGUEMANAGER.CPP TOO

 //DIALOGUE PROPOSAL EVENT
struct dialogueProposalEvent : baseEvent {
    int dialogueNode; 


    dialogueProposalEvent(int node) : dialogueNode(node)  {
        eventName = "dialogueProposalEvent"; 
    }

    void dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx) override;
};

//START DIALOGUE EVENT
struct startDialogueEvent : baseEvent {
    int dialogueNode; 
    int entityId = -1;
    position entityPos = { -100.0f, -100.0f };
    startDialogueEvent(int node) : dialogueNode(node) {
        eventName = "startDialogueEvent"; 
    }

    void dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx) override; 
};

struct setUpDialogueBubbleEvent : baseEvent {
    int entityId; 
    position entityPos = { -100.0f, -100.0f };

    setUpDialogueBubbleEvent(int id) : entityId(id) {
        eventName = "setupDialogueBubbleEvent"; 
    }

    void dispatch(movementManager& m, entityManager& entity, dialogueManager& d, renderCacheManager& r, turnContext& ctx) override;
};