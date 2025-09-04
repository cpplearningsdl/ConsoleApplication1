#include "northMovement.h"

northMovement::northMovement(float startX, float startY, float distance, int frames)
	: x(startX), y(startY), totalFrames(frames), currentFrame(0)
{
	if (totalFrames <= 0) totalFrames = 1; // prevent divide by zero
	deltaY = -distance / static_cast<float>(totalFrames); // negative Y for north
}

void northMovement::step() {
	if (currentFrame < totalFrames) {
		y += deltaY;
		currentFrame++;
	}
}

float northMovement::getX() const { return x; }
float northMovement::getY() const { return y; }
bool northMovement::isFinished() const { return currentFrame >= totalFrames; }
