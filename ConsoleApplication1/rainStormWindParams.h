#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

struct rainWindParams {
    float startAngleDeg = 90.0f;      // mandatory
    float angleVariance = 3.0f;
    float angleChangePerSecond = 0.0f;
};

inline void to_json(json& j, const rainWindParams& rwp) {
    j = json::object();
    j["startAngleDeg"] = rwp.startAngleDeg;
    j["angleVariance"] = rwp.angleVariance;
    j["angleChangePerSecond"] = rwp.angleChangePerSecond;

}

inline void from_json(const json& j, rainWindParams& rwp) {

    j.at("startAngleDeg").get_to(rwp.startAngleDeg);
    j.at("angleVariance").get_to(rwp.angleVariance);
    j.at("angleChangePerSecond").get_to(rwp.angleChangePerSecond);
}