#pragma once
#include <variant>
#include "event.h"
//turn 
#include "turnEvents.h"
//dialogue
#include "dialogueEvents.h"
//movement
#include "movementEvents.h"
#include "enteredTileEvent.h" 
#include "entityDied.h"


using gameEvent = std::variant<
	//turn
	newTurnEvent,
	startTurnEvent,
	//dialogue
	dialogueProposalEvent,
	startDialogueEvent,
	//movement
	movementProposedEvent,
	enteredTileEvent,
	finishedMovementEvent,
	finishedPathEvent,
	entityDiedEvent
>;
