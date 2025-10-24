#pragma once
#include "event.h"

struct updateRenderInfoEvent : baseEvent { 
	int entityId;
	int tileId;
};
