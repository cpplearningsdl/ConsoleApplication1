#pragma once
#include "animationMovement.h"
class southMovement : public animationMovement
{
private:
	float x, y;
	float deltaY;
	int totalFrames;
	int currentFrame;

public:
	southMovement(float startX, float startY, float distance, int frames);

	void step() override;
	float getX() const override;
	float getY() const override;
	bool isFinished() const override;
};

