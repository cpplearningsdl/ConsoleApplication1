#pragma once
#include "animationMovement.h"
#include "movementTypeEnum.h"
#include "json.hpp"

class northMovement : public animationMovement {
private:  
	float deltaY;
	int totalFrames;
	int currentFrame;

public:
	northMovement(int startX, int startY, float distance, int frames); 
	northMovement(const northMovement& other);
	void loadFromJson(const nlohmann::ordered_json& j) override;
	void to_json(nlohmann::ordered_json& j) const override;

	void step() override; 
	bool isFinished() const override;
	 
	std::unique_ptr<animationMovement> clone() const override;
	

};

