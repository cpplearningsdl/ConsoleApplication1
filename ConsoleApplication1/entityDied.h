#pragma once
#include "event.h"


struct entityDiedEvent : baseEvent {
	entity* ent;
	int killerId;
};

