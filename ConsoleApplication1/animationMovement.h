#pragma once
#include "json.hpp"
#include <memory>
class animationMovement {
public:
	virtual ~animationMovement() = default;
	virtual std::unique_ptr<animationMovement> clone() const = 0;
	virtual void loadFromJson(const nlohmann::ordered_json& j) = 0;

	virtual void step() = 0; 
	virtual bool isFinished() const = 0;

	virtual float getX() const = 0;
	virtual float getY() const = 0;
};