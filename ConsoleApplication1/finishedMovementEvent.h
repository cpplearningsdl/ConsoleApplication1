#pragma once
#include "event.h"
#include "position.h"

struct finishedMovementEvent : baseEvent {
	entity* ent;
	int entityId;
	position pos;
};
