#pragma once
#include "turnContext.h"
#include "turnManager.h"
#include "entityManager.h"
#include "movementManager.h"
//#include "battleManager.h"
#include "dialogueManager.h"
#include "renderCacheManager.h"
#include "event.h"

inline void handleEvents(turnContext& ctx, entityManager& entities, movementManager& move, renderCacheManager& renderCache, dialogueManager& dialogue) {
    ctx.eventLog = "////// \n";
    while (!ctx.events.empty())
    {
        // get pointer to the event at the front
        std::unique_ptr<baseEvent> ev = std::move(ctx.events.front());
        ctx.events.pop_front();
        logManager::logThis("PoppedEvent", ev->eventName + " " + ev->eventPhaseToString());
  
        ev->dispatch(move, entities, dialogue, renderCache, ctx);
        
        ctx.eventLog = ctx.eventLog + ev->eventName + " " + ev->eventPhaseToString() + "\n";
        if (ev->phase == eventPhase::PROCESS && ev->convertToExecuteAfterProcessing) {
            ev->phase = eventPhase::EXECUTE;
            ctx.events.emplace_front(std::move(ev));
        }
    }
    logManager::logThis(ctx.eventLog);
}
