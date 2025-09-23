#pragma once
#include "json.hpp"

class dimensions {

private:
	int w, h;
public:
	dimensions(int nw, int nh) : w(nw), h(nh) {}
	dimensions() : w(0), h(0) {}

	void setSize(int nw, int nh) { w = nw, h = nh; }
	void setW(int nw) { w = nw; }
	void setH(int nh) { h = nh; }
	int getW() const { return w; }
	int getH() const { return h; }

	friend void to_json(nlohmann::ordered_json& j, const dimensions& size);
	friend void from_json(const nlohmann::ordered_json& j, dimensions& size);
};

inline void to_json(nlohmann::ordered_json& j, const dimensions& size) {
	j = nlohmann::ordered_json{
	{"w", size.getW()},
	{"h", size.getH()},
	};
}
inline void from_json(const nlohmann::ordered_json& j, dimensions& size) {
	size.setSize(j.value("w", 0), j.value("h", 0));
}