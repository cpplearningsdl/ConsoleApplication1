#pragma once
#include <vector>
#include "json.hpp"
#include "rainStormSizeAnimationParams.h"

using json = nlohmann::ordered_json;

struct rainStormSizeAnimationSequence {
	std::vector<rainStormSizeAnimationParams> sequence;
	int step = 0; 
	bool animate = false;
};

inline void to_json(json& j, const rainStormSizeAnimationSequence& sas) {
	j = json::object();
	j["sequence"] = sas.sequence;
	j["step"] = sas.step;
	j["animate"] = sas.animate;
}

inline void from_json(const json& j, rainStormSizeAnimationSequence& sas) {
	j.at("sequence").get_to(sas.sequence);
	j.at("step").get_to(sas.step);
	j.at("animate").get_to(sas.animate);
}

 
 