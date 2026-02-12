#pragma once
#include "json.hpp"


using json = nlohmann::ordered_json;

struct rainWindState {
    float currentAngleDeg;
    float externalAngleOffset;
};

inline void to_json(json& j, const rainWindState& rwp) {
    j = json::object();
    j["currentAngleDeg"] = rwp.currentAngleDeg;
    j["externalAngleOffset"] = rwp.externalAngleOffset;

}

inline void from_json(const json& j, rainWindState& rwp) {

    j.at("currentAngleDeg").get_to(rwp.currentAngleDeg);
    j.at("externalAngleOffset").get_to(rwp.externalAngleOffset);
}