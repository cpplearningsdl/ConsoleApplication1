#pragma once
#include "event.h"
#include "path.h"


class entity;

struct movementProposedEvent : baseEvent {
    entity* mover;
    int entityId;
    movementPath newPath;
    bool accepted;

    movementProposedEvent(
        entity* e,
        int id,
        movementPath nPath,
        bool b
    )
        : baseEvent(eventType::movementProposed)   // REQUIRED
        , mover(e)
        , entityId(id)
        , newPath(nPath)
        , accepted(b)
    {
    }
};
struct finishedMovementEvent : baseEvent {
    entity* ent;
    int entityId;
    position pos;

    finishedMovementEvent(entity* e, int id, position p)
        : baseEvent(eventType::finishedMovement)   // REQUIRED
        , ent(e)
        , entityId(id)
        , pos(p)
    {
    }
};

struct finishedPathEvent : baseEvent {
	entity* ent;
	int entityId; 
	position pos;
	finishedPathEvent(entity* e, int id, position p)
		: baseEvent(eventType::finishedPath)   // <-- THIS IS REQUIRED
		, ent(e)
		, entityId(id)
		, pos(p)
	{
	}
};
