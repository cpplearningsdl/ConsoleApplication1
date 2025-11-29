#pragma once
#include "turnContext.h"
#include "turnManager.h"
#include "movementManager.h"
//#include "battleManager.h"
#include "dialogueManager.h"
#include "renderCacheManager.h"
#include "event.h"

inline void handleEvents(turnContext& ctx, movementManager& move, renderCacheManager& renderCache, dialogueManager& dialogue) {
    while (!ctx.events.empty())
    {
        // get pointer to the event at the front
        std::unique_ptr<baseEvent> ev = std::move(ctx.events.front());
        ctx.events.pop_front();

  
        ev->process(ctx, move);
        ev->process(ctx, dialogue);
       //e->process(ctx, renderCache);

        // execute phase
        ev->execute(ctx, move);
        ev->execute(ctx, dialogue);
       //v->execute(ctx, renderCache);
    }
}
 