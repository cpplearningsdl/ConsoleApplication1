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

  
        ev->dispatch(move, dialogue, renderCache, ctx);

        if (ev->phase == eventPhase::PROCESS && ev->convertToExecuteAfterProcessing) {
            ev->phase = eventPhase::EXECUTE;
            ctx.events.emplace_front(std::move(ev));
        }
    }
}
 