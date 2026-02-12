#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

struct rainVelocityParams {
    float min = 0.0f;
    float max = 1000.0f;
};

inline void to_json(json& j, const rainVelocityParams& rwp) {
    j = json::object();
    j["min"] = rwp.min;
    j["max"] = rwp.max;

}

inline void from_json(const json& j, rainVelocityParams& rwp) {

    j.at("min").get_to(rwp.min);
    j.at("max").get_to(rwp.max);
}