#include "animationMovementFactory.h"
#include "idleMovement.h"
#include "northMovement.h"
//#include "southMovement.h"
//#include "eastMovement.h"
//#include "westMovement.h"
#include "vectorToMovement.h"

std::unique_ptr<animationMovement> animationMovementFactory::createMovement(movementTypeEnum type, float startX, float startY, float distance, int frames, float destinationX, float destinationY) {
	switch (type) {
	case movementTypeEnum::north:
		return std::make_unique<northMovement>(startX, startY, distance, frames);
	case movementTypeEnum::idle:
		return std::make_unique<idleMovement>(startX, startY);
	//case movementTypeEnum::south:
	//	return std::make_unique<southMovement>(startX, startY, distance, frames);
	//case movementDirectionEnum::east:
	//	return std::make_unique<eastMovement>(startX, startY, distance, frames);
	//case movementDirectionEnum::west:
	//	return std::make_unique<westMovement>(startX, startY, distance, frames);
	case movementTypeEnum::vectorTo:
		return std::make_unique<vectorToMovement>(startX, startY, destinationX, destinationY, frames);
	default:
		return nullptr;
	}
}
 

std::unique_ptr<animationMovement> animationMovementFactory::createFromJson(const nlohmann::ordered_json& j) {
	std::string type = j.at("type").get<std::string>();
	std::unique_ptr<animationMovement> ptr;

	if (type == "north") {
		ptr = std::make_unique<northMovement>(0, 0, 0, 1); // dummy init
	} else
	if (type == "idle") {
		ptr = std::make_unique<idleMovement>(0, 0);
	}else
		if (type == "vectorTo") {//start x, start y, destX, destY, frames
			ptr = std::make_unique<vectorToMovement>(0, 0, 0, 0, 1);
		}

	if (ptr) {
		ptr->loadFromJson(j); // overwrite with real state
	}
	return ptr;
}