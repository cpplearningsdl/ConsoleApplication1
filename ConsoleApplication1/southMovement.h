#pragma once
#include "animationMovement.h"
class southMovement : public animationMovement {
private:
	float x, y;
	float deltaY;
	int totalFrames;
	int currentFrame;

public:
	southMovement(float startX, float startY, float distance, int frames);
	southMovement(const southMovement& other);

	void step() override;
	float getX() const override;
	float getY() const override;
	bool isFinished() const override;
	 
	std::unique_ptr<animationMovement> clone() const override;
};

