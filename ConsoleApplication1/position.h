#pragma once
#include "json.hpp"

class position {

private:
	int x, y;
public:
	position(int nx, int ny) : x(nx), y(ny) {}
	position() : x(0), y(0) {}

	void setPosition(int nx, int ny) { x = nx, y = ny; } 
	void setX(int nx) { x = nx; }
	void setY(int ny) { y = ny; }
	int getX() const {return x; }
	int getY() const { return y; }

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
	pos.setPosition(j.value("x", 0),j.value("y",0)); 
}