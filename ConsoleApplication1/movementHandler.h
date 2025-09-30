#pragma once
#include "entity.h"
#include "logManager.h"
#include "path.h"

inline void handleMovement(entity& e) {
	animationManager& eam = e.getAnimationManager();

	if (e.moving())	{
		if (eam.isFinished()) {
			movementPath& p = e.getPath();
			if (p.turns.size() > 0) {
				eam.setMovement(getNextDirection(p), 0, 0, 128, 10);
			}
			else {
				e.setMoving(false);
				e.setBlockMenus(false);
				eam.loadAnimation("idle");
				eam.setMovement(movementTypeEnum::idle, 0, 0, 0, eam.getFrameCount());
			}

		}
	}
}
