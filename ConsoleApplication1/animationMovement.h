#pragma once

class animationMovement {
public:
	virtual ~animationMovement() = default;

	virtual void step() = 0; 
	virtual bool isFinished() const = 0;

	virtual float getX() const = 0;
	virtual float getY() const = 0;
};