#pragma once
#include <variant>
#include "event.h"
//turn 
#include "turnEvents.h"
//movement
#include "movementPropsalEvent.h"
#include "enteredTileEvent.h"
#include "finishedMovementEvent.h"
#include "finishedPathEvent.h"
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
