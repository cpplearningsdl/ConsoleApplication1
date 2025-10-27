#pragma once
#include "vectorToMovement.h"
#include "logManager.h" 

vectorToMovement::vectorToMovement(float startX, float startY, float targetX, float targetY, int frames)
	: destX(targetX), destY(targetY), totalFrames(frames), currentFrame(0)
{
	setX(startX);
	setY(startY);

	if (totalFrames <= 0) totalFrames = 1;

	float dx = destX - startX;
	float dy = destY - startY;

	deltaX = dx / static_cast<float>(totalFrames);
	deltaY = dy / static_cast<float>(totalFrames);
}

vectorToMovement::vectorToMovement(const vectorToMovement& other)
	: destX(other.destX), destY(other.destY),
	deltaX(other.deltaX), deltaY(other.deltaY),
	totalFrames(other.totalFrames), currentFrame(other.currentFrame)
{
	setX(other.getX());
	setY(other.getY());
}

void vectorToMovement::step() {
	if (currentFrame < totalFrames) {
		setX(getX() + deltaX);
		setY(getY() + deltaY);
		currentFrame++;
		logManager::logThis("X: " + std::to_string( getX()) + ", Y: " + std::to_string( getY()));
	}
}

bool vectorToMovement::isFinished() const {
	return currentFrame >= totalFrames;
}

 

void vectorToMovement::loadFromJson(const nlohmann::ordered_json& j) {
	
	setX(j.value("x", 0.0f));
	setY(j.value("y", 0.0f));
	destX = j.value("destX", 0.0f);
	destY = j.value("destY", 0.0f);
	deltaX = j.value("deltaX", 0.0f);
	deltaY = j.value("deltaY", 0.0f);
	totalFrames = j.value("totalFrames", 1);
	currentFrame = j.value("currentFrame", 0);
}

void vectorToMovement::to_json(nlohmann::ordered_json& j) const {
	j = { 
		{"x", getX()},
		{"y", getY()},
		{"destX", destX},
		{"destY", destY},
		{"deltaX", deltaX},
		{"deltaY", deltaY},
		{"totalFrames", totalFrames},
		{"currentFrame", currentFrame}
	};
}
