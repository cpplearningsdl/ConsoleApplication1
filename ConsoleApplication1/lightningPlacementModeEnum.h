#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::ordered_json;


enum class lightningPlacementMode {
    FIXEDENDPOINTS,        // always start ? end
    RANDOMONSCREEN,        // random start/end in viewport
    RADIUSFROMPOINT,       // random within radius of center
    WALKINGENDPOINTS       // endpoints move over time
};



inline void to_json(json& j, const enum class lightningPlacementMode & lpm) {
    switch (lpm){
    case lightningPlacementMode::FIXEDENDPOINTS:   j = "FIXEDENDPOINTS";   break;
    case lightningPlacementMode::RANDOMONSCREEN: j = "RANDOMONSCREEN"; break;
    case lightningPlacementMode::RADIUSFROMPOINT:   j = "RADIUSFROMPOINT";   break;
    case lightningPlacementMode::WALKINGENDPOINTS:  j = "WALKINGENDPOINTS";  break;
    default:
        j = "RANDOMONSCREEN"; // safety fallback
        break;
    }
}

inline void from_json(const json& j, lightningPlacementMode& m) {
    const std::string s = j.get<std::string>();

    if (s == "FIXEDENDPOINTS")          m = lightningPlacementMode::FIXEDENDPOINTS;
    else if (s == "RANDOMONSCREEN")     m = lightningPlacementMode::RANDOMONSCREEN;
    else if (s == "RADIUSFROMPOINT")    m = lightningPlacementMode::RADIUSFROMPOINT;
    else if (s == "WALKINGENDPOINTS")   m = lightningPlacementMode::WALKINGENDPOINTS;
    else                                m = lightningPlacementMode::RANDOMONSCREEN; // fallback for unknown / old saves
}
