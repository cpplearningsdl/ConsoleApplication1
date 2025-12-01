#pragma once
#include "event.h"
#include "path.h"
#include "movementManager.h"
#include "dialogueManager.h"


class entity;
class movementManager;
class dialogueManager;
class renderManager;

struct movementProposedEvent : baseEvent {
    entity* mover;
    int entityId;
    movementPath newPath;
    bool accepted;

    movementProposedEvent(entity* m, int id, movementPath path, bool a)
        : mover(m), entityId(id), newPath(std::move(path)), accepted(a)
    {
        phase = eventPhase::PROCESS;
    }

    void dispatch(movementManager& move, dialogueManager& dialogue, renderCacheManager& renderCache, turnContext& ctx) override
    {
        move.processMovementProposedEvent(ctx, *this, phase); 
    }
};


struct finishedMovementEvent : baseEvent {
    entity* ent;
    int entityId;
    position pos;

    finishedMovementEvent(entity* e, int id, position p)
        : ent(e), entityId(id), pos(p)
    {
        phase = eventPhase::PROCESS;
    }

    void dispatch(movementManager& move, dialogueManager& dialogue, renderCacheManager& renderCache, turnContext& ctx) override
    {
        move.processFinishedMovementEvent(ctx, *this, phase);
       // renderCache.onFinishedMovement(ctx, *this, phase);
    }
};


struct finishedPathEvent : baseEvent {
    entity* ent;
    int entityId;
    position pos;

    finishedPathEvent(entity* e, int id, position p)
        : ent(e), entityId(id), pos(p)
    {
        phase = eventPhase::PROCESS;
    }

    void dispatch(movementManager& move, dialogueManager& dialogue, renderCacheManager& renderCache, turnContext& ctx) override
    {
        move.processFinishedPathEvent(ctx, *this, phase); 
    }
};

struct movedThisFrameEvent : baseEvent {
    entity* ent;
    int entityId;
    position pos;

    movedThisFrameEvent(entity* e, int i, position p)
        :ent(e), entityId(i), pos(p)
    {
        phase = eventPhase::EXECUTE;
    }

    void dispatch(movementManager& move, dialogueManager& dialogue, renderCacheManager& renderCache, turnContext& ctx) override
    {
        dialogue.processMovedThisFrameEvent(ctx, *this, phase);
    }

};