#pragma once
#include "animationMovement.h"
#include "movementTypeEnum.h"
#include "json.hpp"
#include <cmath>

class vectorToMovement : public animationMovement {
private:
	float destX;
	float destY;
	float deltaX;
	float deltaY;
	int totalFrames;
	int currentFrame; 

public:
	vectorToMovement(float startX, float startY, float targetX, float targetY, int frames);
	vectorToMovement(const vectorToMovement& other);

	void step() override;
	bool isFinished() const override;

	void loadFromJson(const nlohmann::ordered_json& j) override;
	void to_json(nlohmann::ordered_json& j) const override;
	movementTypeEnum getMovementType() const override { return movementTypeEnum::vectorTo; }

	std::unique_ptr<animationMovement> clone() const override;
};
