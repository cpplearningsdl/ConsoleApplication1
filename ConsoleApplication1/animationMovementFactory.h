#pragma once
#include <memory>
#include <string>
#include "json.hpp"
#include "animationMovement.h" 
#include "movementTypeEnum.h"

class animationMovementFactory {
public:
		// Creates and returns a unique_ptr to the requested movement
		static std::unique_ptr<animationMovement> createMovement(movementTypeEnum  type, float startX, float startY, float distance = 0.0f, int frames = 0, float destinationX = 0.0f, float destinationY = 0.0f); 
		static std::unique_ptr<animationMovement> createFromJson( const nlohmann::ordered_json& j );
};
