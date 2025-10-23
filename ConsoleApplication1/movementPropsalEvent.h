#pragma once
#include "event.h"
#include "position.h"

class entity;
// Example event subtypes
struct movementProposedEvent : baseEvent {
	entity* mover;
	int entityId;
	position pos;
	bool accepted = false; // can be flipped by systems that approve/reject
};