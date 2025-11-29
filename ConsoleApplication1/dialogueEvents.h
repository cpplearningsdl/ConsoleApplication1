#pragma once
#include "event.h"
#include "path.h"


class entity;
class movementManager;
class dialogueManager;

struct dialogueProposalEvent : baseEvent {
    int  dialogueNode;
    bool accepted;

    dialogueProposalEvent(int d, bool a)
        : baseEvent{ },
        dialogueNode(d),
        accepted(a)
    {
    }

    void process(turnContext& ctx, dialogueManager& dia) override;
    void execute(turnContext& ctx, dialogueManager& dia) override;
};

struct startDialogueEvent : baseEvent {
	int dialogueNode;
    startDialogueEvent(int d)
        : baseEvent{ },
        dialogueNode(d)
        {}

    void process(turnContext& ctx, dialogueManager& dia) override;
    void execute(turnContext& ctx, dialogueManager& dia) override;
};
