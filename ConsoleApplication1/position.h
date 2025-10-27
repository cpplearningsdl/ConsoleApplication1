#pragma once
#include "json.hpp"

class position {

private:
	float x, y;
public:
	position(float nx, float ny) : x(nx), y(ny) {}
	position() : x(0), y(0) {}

	void setPosition(float nx, float ny) { x = nx, y = ny; } 
	void setX(float nx) { x = nx; }
	void setY(float ny) { y = ny; }
	float getX() const {return x; }
	float getY() const { return y; }

	friend void to_json(nlohmann::ordered_json& j, const position& pos);
	friend void from_json(const nlohmann::ordered_json& j, position& pos);
};

inline void to_json(nlohmann::ordered_json& j, const position& pos) {
	j = nlohmann::ordered_json{
	{"x", pos.getX()},
	{"y", pos.getY()},
	};
}
inline void from_json(const nlohmann::ordered_json& j, position& pos) {
	float xd = j.value("x", 0.0f);
	float yd = j.value("y", 0.0f);
	pos.setPosition(xd, yd);
}