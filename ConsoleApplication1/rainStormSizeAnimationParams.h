#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

struct rainStormSizeAnimationParams {
	bool shrinkW = false;
	bool shrinkH = false;
	bool growW = false;
	bool growH = false;
	bool shrinkKillW = false;
	bool shrinkKillH = false;
	bool growKillW = false;
	bool growKillH = false;
	bool hold = false;
	float speed = 0.0f;
	float duration = 0.0f;
};

inline void to_json(json& j, const rainStormSizeAnimationParams& s) {
	j = json::object();
	j["shrinkW"] = s.shrinkW;
	j["shrinkH"] = s.shrinkH;
	j["growW"] = s.growW; 
	j["grow"] = s.growH;

	j["shrinkKillW"] = s.shrinkKillW;
	j["shrinkKillH"] = s.shrinkKillH;
	j["growKillW"] = s.growKillW;
	j["growKillH"] = s.growKillH;

	j["hold"] = s.hold;
	j["speed"] = s.speed;
	j["duration"] = s.duration;
}

inline void from_json(const json& j, rainStormSizeAnimationParams& s) {
	j.at("shrinkW").get_to(s.shrinkW);
	j.at("shrinkH").get_to(s.shrinkH);
	j.at("growW").get_to(s.growW); 
	j.at("growH").get_to(s.growH);

	j.at("shrinkKillW").get_to(s.shrinkKillW);
	j.at("shrinkKillH").get_to(s.shrinkKillH);
	j.at("growKillW").get_to(s.growKillW);
	j.at("growKillH").get_to(s.growKillH);

	j.at("hold").get_to(s.hold);
	j.at("speed").get_to(s.speed);
	j.at("duration").get_to(s.duration);
}
 