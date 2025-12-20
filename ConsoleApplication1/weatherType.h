#pragma once
#include "json.hpp" 
#include <string> 

using json = nlohmann::ordered_json;

enum class weatherType {
    CLEAR,
    CLOUDY,
    RAIN,
    STORM,
    FOG
};

inline void to_json(json& j, const weatherType& w) {
    switch (w) {
    case weatherType::CLEAR:   j = "clear";   break;
    case weatherType::CLOUDY: j = "cloudy"; break;
    case weatherType::RAIN:   j = "rain";   break;
    case weatherType::STORM:  j = "storm";  break;
    case weatherType::FOG:    j = "fog";    break;
    default:
        j = "clear"; // safety fallback
        break;
    }
}

inline void from_json(const json& j, weatherType& w) {
    const std::string s = j.get<std::string>();

    if (s == "clear")   w = weatherType::CLEAR;
    else if (s == "cloudy") w = weatherType::CLOUDY;
    else if (s == "rain")   w = weatherType::RAIN;
    else if (s == "storm")  w = weatherType::STORM;
    else if (s == "fog")    w = weatherType::FOG;
    else                    w = weatherType::CLEAR; // fallback for unknown / old saves
}
