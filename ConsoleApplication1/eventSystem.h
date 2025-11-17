#pragma once
#include "turnContext.h"
#include "turnManager.h"
#include "movementManager.h"
//#include "battleManager.h"
#include "dialogueManager.h"
#include "renderCacheManager.h"

inline void handleEvents(turnContext& ctx, movementManager& move, renderCacheManager& renderCache, dialogueManager& dialogue) {
	for (auto& ev : ctx.events) {
		move.processEvent(ctx, ev);
		dialogue.processEvent(ctx, ev);
		//battle.handleEvent(ctx,ev);
		renderCache.processEvent(ctx, ev);
	}

	for (auto& ev : ctx.events) {
		move.executeEvent(ctx, ev);
		dialogue.executeEvent(ctx, ev);
		//battle.handleEvent(ctx, ev);
		renderCache.executeEvent(ctx, ev);
	}
	ctx.events.clear();
}
 