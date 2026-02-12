#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

struct rainVelocityState {
	float scale = 1.0f;

};

inline void to_json(json& j, const rainVelocityState& rvs) {
	j = json::object();
	j["start"] = rvs.scale;

}

inline void from_json(const json& j, rainVelocityState& rvs) { 
	j.at("scale").get_to(rvs.scale);
}