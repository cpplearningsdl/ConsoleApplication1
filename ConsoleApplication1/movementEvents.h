#pragma once
#include "event.h"
#include "path.h" 


class entity;
class movementManager;
class dialogueManager;
class entityManager;
class renderManager;

struct movementProposedEvent : baseEvent {
    entity* mover;
    int entityId;
    movementPath newPath;
    bool accepted;

    movementProposedEvent(entity* m, int id, movementPath path, bool a)
        : mover(m), entityId(id), newPath(std::move(path)), accepted(a)
    {
        eventName = "MovementProposedEvent";
        phase = eventPhase::PROCESS;
    }

    void dispatch(movementManager& move, entityManager& entities, dialogueManager& dialogue, renderCacheManager& renderCache, turnContext& ctx) override;
};


struct finishedMovementEvent : baseEvent {
    entity* ent;
    int entityId;
    position pos;

    finishedMovementEvent(entity* e, int id, position p)
        : ent(e), entityId(id), pos(p)
    {
        eventName = "finishedMovementEvent";
        phase = eventPhase::PROCESS;
    }

    void dispatch(movementManager& move, entityManager& entities, dialogueManager& dialogue, renderCacheManager& renderCache, turnContext& ctx) override;
};


struct finishedPathEvent : baseEvent {
    entity* ent;
    int entityId;
    position pos;

    finishedPathEvent(entity* e, int id, position p)
        : ent(e), entityId(id), pos(p)
    {
        eventName = "finishedPathEvent";
        phase = eventPhase::PROCESS;
    }

    void dispatch(movementManager& move, entityManager& entities, dialogueManager& dialogue, renderCacheManager& renderCache, turnContext& ctx) override;
};

struct movedThisFrameEvent : baseEvent {
    entity* ent;
    int entityId;
    position pos;

    movedThisFrameEvent(entity* e, int i, position p)
        :ent(e), entityId(i), pos(p)
    {
        eventName = "movedThisFrameEvent";
        phase = eventPhase::EXECUTE;
    }

    void dispatch(movementManager& move, entityManager& entities, dialogueManager& dialogue, renderCacheManager& renderCache, turnContext& ctx) override;

};