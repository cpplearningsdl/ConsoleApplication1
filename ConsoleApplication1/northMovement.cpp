#include "northMovement.h"

northMovement::northMovement(float startX, float startY, float distance, int frames)
	: x(startX), y(startY), deltaY(distance / frames), totalFrames(frames), currentFrame(0)
{
	if (totalFrames <= 0) totalFrames = 1;
	deltaY = distance / static_cast<float>(totalFrames); 
}

northMovement::northMovement(const northMovement& other)
	: x(other.x), y(other.y), deltaY(other.deltaY), totalFrames(other.totalFrames), currentFrame(other.currentFrame)
{
}

void northMovement::loadFromJson(const nlohmann::ordered_json& j){ 
	x = j.value("x", 0.0f);
	y = j.value("y", 0.0f);
	deltaY = j.value("deltaY", 0.0f);
	totalFrames = j.value("totalFrames", 1);
	currentFrame = j.value("currentFrame", 0);
}
void northMovement::to_json(nlohmann::ordered_json& j) const {
	j = { 
		{"type", movementTypeEnumToString(movementTypeEnum::north)},
		{"x", x},
		{"y", y},
		{"deltaY", deltaY},
		{"totalFrames", totalFrames},
		{"currentFrame", currentFrame}
	};
}
void northMovement::step() {
	if (currentFrame < totalFrames) {
		y -= deltaY; // moves north
		currentFrame++;
	}
}

float northMovement::getX() const { return x; }
float northMovement::getY() const { return y; }
bool northMovement::isFinished() const { return currentFrame >= totalFrames; }

std::unique_ptr<animationMovement> northMovement::clone() const {
	return std::make_unique<northMovement>(*this);
}
