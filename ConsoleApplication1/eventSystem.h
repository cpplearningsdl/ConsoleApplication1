#pragma once
// eventSystem.h
#pragma once
#include "turnContext.h"
#include "turnManager.h"
#include "movementManager.h"
//#include "battleManager.h"
#include "renderCacheManager.h"

inline void processEvents(turnContext& ctx,	movementManager& move, renderCacheManager& renderCache){
	for (auto& ev : ctx.events) {
		move.handleEvent(ctx, ev); 
		//battle.handleEvent(ctx,ev);
		renderCache.handleEvent(ctx, ev);
	}

	// move any deferred events into next frame if needed
	ctx.events.clear();
	//ctx.events.swap(ctx.nextEvents);
}
