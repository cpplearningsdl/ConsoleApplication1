#pragma once
#include "json.hpp"

class dimensions {

private://UPDATE TO FLOAT
	float width, height;
public:
	dimensions(float nw, float nh) : width(nw), height(nh) {}
	dimensions() : width(0), height(0) {}

	void setSize(float nw, float nh) { width = nw, height = nh; }
	void setW(float nw) { width = nw; }
	void setH(float nh) { height = nh; }
	float getW() const { return width; }
	float getH() const { return height; } 

	friend void to_json(nlohmann::ordered_json& j, const dimensions& size);
	friend void from_json(const nlohmann::ordered_json& j, dimensions& size);
};

inline void to_json(nlohmann::ordered_json& j, const dimensions& size) {
	j = nlohmann::ordered_json{
	{"width", size.getW()},
	{"height", size.getH()},
	};
}
inline void from_json(const nlohmann::ordered_json& j, dimensions& size) {
	size.setSize(j.value("width", 0.0f), j.value("height", 0.0f));
}