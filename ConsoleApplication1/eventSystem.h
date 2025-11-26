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

        // process phase
        move.processEvent(ctx, ev.get());
        dialogue.processEvent(ctx, ev.get());
        // battle.processEvent(ctx, ev.get());
        renderCache.processEvent(ctx, ev.get());

        // execute phase
        move.executeEvent(ctx, ev.get());
        dialogue.executeEvent(ctx, ev.get());
        // battle.executeEvent(ctx, ev.get());
        renderCache.executeEvent(ctx, ev.get());
    }
}
 