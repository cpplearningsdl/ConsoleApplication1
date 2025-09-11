#pragma once
#include <memory>
#include <string>
#include "animationMovement.h" 
#include "movementDirectionEnum.h"

class animationMovementFactory {
public:
		// Creates and returns a unique_ptr to the requested movement
		static std::unique_ptr<animationMovement> createMovement(movementDirectionEnum  type, float startX, float startY, float distance, int frames );
};
