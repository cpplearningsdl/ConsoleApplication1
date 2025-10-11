#pragma once
#include "json.hpp"

class dimensions {

private://UPDATE TO FLOAT
	int width, height;
public:
	dimensions(int nw, int nh) : width(nw), height(nh) {}
	dimensions() : width(0), height(0) {}

	void setSize(int nw, int nh) { width = nw, height = nh; }
	void setW(int nw) { width = nw; }
	void setH(int nh) { height = nh; }
	int getW() const { return width; }
	int getH() const { return height; }
	float getWf() const { return static_cast<float>(width); }
	float getHf() const { return static_cast<float>(height); }

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
	size.setSize(j.value("width", 0), j.value("height", 0));
}