#pragma once
#include "event.h"
#include "path.h"


class entity;
class movementManager;
class dialogueManager;

struct movementProposedEvent : baseEvent {
    entity* mover;
    int entityId;
    movementPath newPath;
    bool accepted;

    movementProposedEvent(entity* m, int id, movementPath path, bool a)
        : mover(m), entityId(id), newPath(std::move(path)), accepted(a) {
    }
     
    void process(turnContext& ctx, movementManager& move) override;
    void execute(turnContext& ctx, movementManager& move) override;
     
};

struct finishedMovementEvent : baseEvent {
    entity* ent;
    int entityId;
    position pos;

    finishedMovementEvent(entity* e, int id, position p)
        : ent(e)
        , entityId(id)
        , pos(p)
    {
    } 
    void process(turnContext& ctx, movementManager& move) override;
    void execute(turnContext& ctx, movementManager& move) override; 
};

struct finishedPathEvent : baseEvent {
	entity* ent;
	int entityId; 
	position pos;
	finishedPathEvent(entity* e, int id, position p)
		: ent(e)
		, entityId(id)
		, pos(p)
	{
	} 
    void process(turnContext& ctx, movementManager& move) override;
    void execute(turnContext& ctx, movementManager& move) override; 
};
