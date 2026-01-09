#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::ordered_json;


enum class lightningPlacementMode {
    FIXEDENDPOINTS,        // always start ? end
    RANDOMONSCREEN,        // random start/end in viewport
    RANDOMONSCREENVERTICAL,
    RANDOMSCREENVERTICALFROMTOP,
    RADIUSFROMPOINT,       // random within radius of center
    SPAWNAROUNDRADIUS,
    WALKINGENDPOINTS,       // endpoints move over time
    GOTOPOINT
};



inline void to_json(json& j, const enum class lightningPlacementMode & lpm) {
    switch (lpm){
    case lightningPlacementMode::FIXEDENDPOINTS:   j = "FIXEDENDPOINTS";   break;
    case lightningPlacementMode::RANDOMONSCREEN: j = "RANDOMONSCREEN"; break;
    case lightningPlacementMode::RANDOMONSCREENVERTICAL: j = "RANDOMONSCREENVERTICAL"; break;
    case lightningPlacementMode::RANDOMSCREENVERTICALFROMTOP: j = "RANDOMSCREENVERTICALFROMTOP"; break;
    case lightningPlacementMode::RADIUSFROMPOINT:   j = "RADIUSFROMPOINT";   break;
    case lightningPlacementMode::SPAWNAROUNDRADIUS:   j = "SPAWNAROUNDRADIUS";   break;
    case lightningPlacementMode::WALKINGENDPOINTS:  j = "WALKINGENDPOINTS";  break;
    case lightningPlacementMode::GOTOPOINT:  j = "GOTOPOINT";  break;
    default:
        j = "RANDOMONSCREEN"; // safety fallback
        break;
    }
}

inline void from_json(const json& j, lightningPlacementMode& m) {
    const std::string s = j.get<std::string>();

    if (s == "FIXEDENDPOINTS")          m = lightningPlacementMode::FIXEDENDPOINTS;
    else if (s == "RANDOMONSCREEN")     m = lightningPlacementMode::RANDOMONSCREEN;
    else if (s == "RANDOMONSCREENVERTICAL")     m = lightningPlacementMode::RANDOMONSCREENVERTICAL;
    else if (s == "RANDOMSCREENVERTICALFROMTOP")     m = lightningPlacementMode::RANDOMSCREENVERTICALFROMTOP;
    else if (s == "RADIUSFROMPOINT")    m = lightningPlacementMode::RADIUSFROMPOINT;
    else if (s == "SPAWNAROUNDRADIUS")    m = lightningPlacementMode::SPAWNAROUNDRADIUS;
    else if (s == "WALKINGENDPOINTS")   m = lightningPlacementMode::WALKINGENDPOINTS;
    else if (s == "GOTOPOINT")   m = lightningPlacementMode::GOTOPOINT;
    else                                m = lightningPlacementMode::RANDOMONSCREEN; // fallback for unknown / old saves
}
