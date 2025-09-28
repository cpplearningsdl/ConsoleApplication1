#pragma once
#include "path.h"
#include "json.hpp"
#include <memory>
class animationMovement {
private:
	int x;
	int y;


public:
	virtual ~animationMovement() = default;
	virtual std::unique_ptr<animationMovement> clone() const = 0;
	virtual void loadFromJson(const nlohmann::ordered_json& j) = 0;
	virtual void to_json(nlohmann::ordered_json& j) const = 0;

	virtual void step() = 0; 
	virtual bool isFinished() const = 0;

	int getX() const { return x;	}
	int getY() const { return y;	}
	void setX(int nx) { x = nx; }
	void setY(int ny) { y = ny; }

};