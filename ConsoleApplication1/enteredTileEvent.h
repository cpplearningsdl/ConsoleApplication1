#pragma once
#include "event.h"

struct enteredTileEvent : baseEvent {
	entity* ent;
	int entityId;
	int tileId;
};
