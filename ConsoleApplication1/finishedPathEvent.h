#pragma once
#include "event.h"
#include "position.h"

struct finishedPathEvent : baseEvent {
	entity* ent;
	int entityId;
	position pos;
};
