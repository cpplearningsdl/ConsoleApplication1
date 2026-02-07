#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

enum class motionTimingMode {
    PER_PARTICLE,
    PER_STORM
};

inline void to_json(json& j, const motionTimingMode& mtm) {
    j = json::object();
    switch (mtm) {
    case motionTimingMode::PER_PARTICLE:   j = "per_particle";   break;
    case motionTimingMode::PER_STORM: j = "per_storm"; break;
    default:
        j = "PER_PARTICLE";
        break;
    }

} 

inline void from_json(const json& j,motionTimingMode& mtm) {
    const std::string s = j.get<std::string>();

    if (s == "per_particle")   mtm = motionTimingMode::PER_PARTICLE;
    else if (s == "per_storm") mtm = motionTimingMode::PER_STORM;
    else { mtm = motionTimingMode::PER_PARTICLE; };
}
