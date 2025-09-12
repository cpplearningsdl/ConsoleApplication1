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
