#include "northMovement.h"

northMovement::northMovement(float startX, float startY, float distance, int frames)
	: deltaY(distance / frames), totalFrames(frames), currentFrame(0)
{
	setX(startX);
	setY(startY);
	if (totalFrames <= 0) totalFrames = 1;
	deltaY = distance / static_cast<float>(totalFrames); 
}

northMovement::northMovement(const northMovement& other)
	: deltaY(other.deltaY), totalFrames(other.totalFrames), currentFrame(other.currentFrame)
{
	setX(other.getX());
	setY(other.getY());
}


	void northMovement::step() {
		if (currentFrame < totalFrames) {
			setY(getY() - deltaY); 
			currentFrame++;
			logManager::logThis("Y: ", getY());
		}
	}
 
bool northMovement::isFinished() const { return currentFrame >= totalFrames; }

std::unique_ptr<animationMovement> northMovement::clone() const {
	return std::make_unique<northMovement>(*this);
}
void northMovement::loadFromJson(const nlohmann::ordered_json& j) {
	setX(j.value("x", 0.0f));
	setY(j.value("y", 0.0f));
	deltaY = j.value("deltaY", 0.0f);
	totalFrames = j.value("totalFrames", 1);
	currentFrame = j.value("currentFrame", 0);
}
void northMovement::to_json(nlohmann::ordered_json& j) const {
	j = {
		{"type", movementTypeEnumToString(movementTypeEnum::north)},
		{"x", getX()},
		{"y", getY()},
		{"deltaY", deltaY},
		{"totalFrames", totalFrames},
		{"currentFrame", currentFrame}
	};
}