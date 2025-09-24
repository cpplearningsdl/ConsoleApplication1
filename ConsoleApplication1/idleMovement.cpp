#include "idleMovement.h"

idleMovement::idleMovement(int startX, int startY)
{ 
	setX(startX);
	setY(startY);
}

idleMovement::idleMovement(const idleMovement& other) 
{
	setX(other.getX());
	setY(other.getY());
}

void idleMovement::loadFromJson(const nlohmann::ordered_json& j) {
	setX( j.value("x", 0));
	setY(j.value("y", 0)); 
}
void idleMovement::to_json(nlohmann::ordered_json& j) const {
	j = {
		{"type", movementTypeEnumToString(movementTypeEnum::idle)},
		{"x", getX()},
		{"y", getY()}
	};
}
 

std::unique_ptr<animationMovement> idleMovement::clone() const {
	return std::make_unique<idleMovement>(*this);
}
