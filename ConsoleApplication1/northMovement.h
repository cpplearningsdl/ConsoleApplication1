#pragma once
#include "animationMovement.h"
class northMovement : public animationMovement {
private:
	float x, y;
	float deltaY;
	int totalFrames;
	int currentFrame;

public:
	northMovement(float startX, float startY, float distance, int frames); 
	northMovement(const northMovement& other);

	void step() override;
	float getX() const override;
	float getY() const override;
	bool isFinished() const override;
	 
	std::unique_ptr<animationMovement> clone() const override;
};