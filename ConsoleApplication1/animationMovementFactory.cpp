#include "animationMovementFactory.h"
#include "northMovement.h"
#include "southMovement.h"
//#include "eastMovement.h"
//#include "westMovement.h"

std::unique_ptr<animationMovement> animationMovementFactory::createMovement(movementTypeEnum type, float startX, float startY, float distance, int frames) {
	switch (type) {
	case movementTypeEnum::north:
		return std::make_unique<northMovement>(startX, startY, distance, frames);
	case movementTypeEnum::south:
		return std::make_unique<southMovement>(startX, startY, distance, frames);
	//case movementTypeEnum::east:
	//	return std::make_unique<eastMovement>(startX, startY, distance, frames);
	//case movementTypeEnum::west:
	//	return std::make_unique<westMovement>(startX, startY, distance, frames);
	default:
		return nullptr;
	}
}
