#pragma once
#include <string>
#include "logManager.h"
#include "turnContext.h"
#include "event.h"
#include "dialogueEvents.h"

void dialogueProposal(turnContext& ctx, baseEvent* ev) {
	auto* e = dynamic_cast<dialogueProposalEvent*>(ev); 
	if (e->accepted) { 
		ctx.emitEvent<startDialogueEvent>(e->dialogueNode);
	}
}