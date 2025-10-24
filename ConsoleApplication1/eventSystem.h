#pragma once
// eventSystem.h
#pragma once
#include "turnContext.h"
#include "movementManager.h"
//#include "battleManager.h"
#include "renderCacheManager.h"

inline void processEvents(turnContext& ctx,	movementManager& move, renderCacheManager& renderCache){
	for (auto& ev : ctx.events) {
		move.handleEvent(ctx, ev); 
		renderCache.handleEvent(ev, ctx);
	}

	// move any deferred events into next frame if needed
	ctx.events.clear();
	//ctx.events.swap(ctx.nextEvents);
}
