#pragma once
#include <variant>
#include "event.h"
#include "movementPropsalEvent.h"
#include "enteredTileEvent.h"
#include "finishedMovementEvent.h"
#include "finishedPathEvent.h"
#include "entityDied.h"


using gameEvent = std::variant<
	//movement
	movementProposedEvent,
	enteredTileEvent,
	finishedMovementEvent,
	finishedPathEvent,
	entityDiedEvent
>;
