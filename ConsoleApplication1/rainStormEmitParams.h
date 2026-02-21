#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;


struct rainEmitParams { 
	float dropsPerSecond = 20.0f;
	float dropLength = 0.0f;//not implemented, this should be changed to emitLength and used for  the amount of time to emit drops, so storm doesnt end with drops not getting to animate to off screen
};

inline void to_json(json& j, const rainEmitParams& rep) {
    j = json::object(); 
    j["dropsPerSecond"] = rep.dropsPerSecond;
    j["dropLength"] = rep.dropLength;
}
 
inline void from_json(const json& j, rainEmitParams& rep) {
    j.at("dropsPerSecond").get_to(rep.dropsPerSecond);
    j.at("dropLength").get_to(rep.dropLength); 
}