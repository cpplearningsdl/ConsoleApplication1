#pragma once
#include <variant>
#include "event.h"
//turn 
#include "turnEvents.h"
//movement
#include "movementEvents.h"
#include "enteredTileEvent.h" 
#include "entityDied.h"


using gameEvent = std::variant<
	//turn
	newTurnEvent,
	startTurnEvent,
	//movement
	movementProposedEvent,
	enteredTileEvent,
	finishedMovementEvent,
	finishedPathEvent,
	entityDiedEvent
>;
