#pragma once
#include "event.h"
#include "path.h"


class entity;
 

struct dialogueProposalEvent : baseEvent {
    int  dialogueNode;
    bool accepted;

    dialogueProposalEvent(int d, bool a)
        : baseEvent{ eventType::dialogueProposal },
        dialogueNode(d),
        accepted(a)
    {
    }
};

struct startDialogueEvent : baseEvent {
	int dialogueNode;
    startDialogueEvent(int d)
        : baseEvent{ eventType::startDialogue },
        dialogueNode(d)
        {}
};
