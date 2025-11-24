#pragma once
#include <string>
#include "logManager.h"
#include "turnContext.h"
#include "event.h"

void dialogueProposal(turnContext& ctx, dialogueProposalEvent& ev) {
	int node = ev.dialogueNode;
	if (ev.accepted) {
		ctx.events.push_back(startDialogueEvent(ev.dialogueNode))
	}
}