#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;


enum class lightModulation {
    None,
    Pulse,        // base ± range
    Oscillation   // base ? base+range ? base
};

inline void to_json(json& j, const lightModulation& m) {
    switch (m) {
    case lightModulation::None:         j = "None"; break;
    case lightModulation::Pulse:        j = "Pulse"; break;
    case lightModulation::Oscillation:  j = "Oscillation"; break;
    }
}

inline void from_json(const json& j, lightModulation& m) {
    const std::string s = j.get<std::string>();

    if (s == "Pulse")              m = lightModulation::Pulse;
    else if (s == "Oscillation")   m = lightModulation::Oscillation;
    else                           m = lightModulation::None;
}