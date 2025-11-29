#pragma once

#include "dialogueEvents.h"
#include "dialogueManager.h" 



void dialogueProposalEvent::process(turnContext& ctx, dialogueManager& dia) {
    // forward to movementManager's strongly-typed handler
    dia.processDialogueProposal(ctx, *this);
}

void dialogueProposalEvent::execute(turnContext& ctx, dialogueManager& dia) {
    dia.executeDialogueProposal(ctx, *this);
}

void startDialogueEvent::process(turnContext& ctx, dialogueManager& dia) {
    // forward to movementManager's strongly-typed handler
    dia.processStartDialogue(ctx, *this);
}

void startDialogueEvent::execute(turnContext& ctx, dialogueManager& dia) {
    dia.executeStartDialogue(ctx, *this);
}