#pragma once
#include "event.h"
#include "path.h"


class entity;

struct movementProposedEvent : baseEvent {
	entity* mover;
	int entityId;
	movementPath newPath;
	bool accepted = true;

	movementProposedEvent(
		entity* e,
		int id,
		movementPath nPath, bool b)
		: mover(e), entityId(id), newPath(nPath), accepted(b) {};
};

struct finishedMovementEvent : baseEvent {
	entity* ent;
	int entityId;
	position pos;
};

struct finishedPathEvent : baseEvent {
	entity* ent;
	int entityId; 

	finishedPathEvent(entity* e, int id)
		: ent(e), entityId(id) {}
};
