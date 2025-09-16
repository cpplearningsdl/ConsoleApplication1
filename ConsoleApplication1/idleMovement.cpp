#include "idleMovement.h"

idleMovement::idleMovement(float startX, float startY)
	: x(startX), y(startY)
{ 
}

idleMovement::idleMovement(const idleMovement& other)
	: x(other.x), y(other.y)
{
}

void idleMovement::loadFromJson(const nlohmann::ordered_json& j) {
	x = j.value("x", 0.0f);
	y = j.value("y", 0.0f); 
}
void idleMovement::to_json(nlohmann::ordered_json& j) const {
	j = {
		{"type", movementTypeEnumToString(movementTypeEnum::idle)},
		{"x", x},
		{"y", y}
	};
}
 

std::unique_ptr<animationMovement> idleMovement::clone() const {
	return std::make_unique<idleMovement>(*this);
}
