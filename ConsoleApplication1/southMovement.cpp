#include "southMovement.h"

southMovement::southMovement(float startX, float startY, float distance, int frames)
	: x(startX), y(startY), totalFrames(frames), currentFrame(0)
{
	if (totalFrames <= 0) totalFrames = 1; // prevent divide by zero
	deltaY = +distance / static_cast<float>(totalFrames); //positive Y for south
}

void southMovement::step() {
	if (currentFrame < totalFrames) {
		y += deltaY;
		currentFrame++;
	}
}

float southMovement::getX() const { return x; }
float southMovement::getY() const { return y; }
bool southMovement::isFinished() const { return currentFrame >= totalFrames; }

