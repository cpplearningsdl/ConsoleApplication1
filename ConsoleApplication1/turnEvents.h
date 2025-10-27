#pragma once
#include "event.h"

struct newTurnEvent : baseEvent {  
};

struct startTurnEvent : baseEvent {
	int entityId; 
};
