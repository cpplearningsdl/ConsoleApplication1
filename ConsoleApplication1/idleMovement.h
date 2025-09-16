#pragma once
#include "animationMovement.h"
#include "movementTypeEnum.h"
#include "json.hpp"

class idleMovement : public animationMovement {
private:
	float x, y; 

public:
	idleMovement(float startX, float startY);
	idleMovement(const idleMovement& other);
	void loadFromJson(const nlohmann::ordered_json& j) override;
	void to_json(nlohmann::ordered_json& j) const override;
	 
	std::unique_ptr<animationMovement> clone() const override;
	 
	float getX() { return x; }
	float getY() { return y; }
	void step() override {};
	bool isFinished() const override { return true; };
};

