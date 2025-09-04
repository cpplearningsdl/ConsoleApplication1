#pragma once
#include <memory>
#include <string>
#include "animationMovement.h" 
#include "movementTypeEnum.h"

class animationMovementFactory {
public:
		// Creates and returns a unique_ptr to the requested movement
		static std::unique_ptr<animationMovement> createMovement( movementTypeEnum  type, float startX, float startY, float distance, int frames );
};
