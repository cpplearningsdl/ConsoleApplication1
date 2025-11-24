#pragma once
#include "turnContext.h"
#include "turnManager.h"
#include "movementManager.h"
//#include "battleManager.h"
#include "dialogueManager.h"
#include "renderCacheManager.h"

inline void handleEvents(turnContext& ctx, movementManager& move, renderCacheManager& renderCache, dialogueManager& dialogue) {
	while (!ctx.events.empty())
	{
		gameEvent ev = ctx.events.front(); 
		ctx.events.pop_front(); 

		move.processEvent(ctx, ev);
		dialogue.processEvent(ctx, ev);
		//battle.handleEvent(ctx,ev);
		renderCache.processEvent(ctx, ev);

		move.executeEvent(ctx, ev);
		dialogue.executeEvent(ctx, ev);
		//battle.handleEvent(ctx, ev);
		renderCache.executeEvent(ctx, ev); 
	}
}
 