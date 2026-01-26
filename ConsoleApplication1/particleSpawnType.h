#pragma once
#include "json.hpp" 
#include <string> 

using json = nlohmann::ordered_json;


enum class particleSpawnType {
    POINT,                  // same point for all particles
    RANDOM_WITHIN_RADIUS,    // per-particle random
    RANDOM_OUTSIDE_RADIUS,   // per-particle random
    RANDOM_BETWEEN_RADII     // per-particle random
};

inline void to_json(json& j, const particleSpawnType& w) {
    switch (w) {
    case particleSpawnType::POINT:   j = "point";   break;
    case particleSpawnType::RANDOM_WITHIN_RADIUS: j = "random_within_radius"; break;
    case particleSpawnType::RANDOM_OUTSIDE_RADIUS:   j = "random_outside_radius";   break;
    case particleSpawnType::RANDOM_BETWEEN_RADII:  j = "random_between_radii";  break;
    default:
        j = "point";
        break;
    }
}

inline void from_json(const json& j, particleSpawnType& w) {
    const std::string s = j.get<std::string>();

    if (s == "point")   w = particleSpawnType::POINT;
    else if (s == "random_within_radius") w = particleSpawnType::RANDOM_WITHIN_RADIUS;
    else if (s == "random_outside_radius")   w = particleSpawnType::RANDOM_OUTSIDE_RADIUS;
    else if (s == "random_between_radii")  w = particleSpawnType::RANDOM_BETWEEN_RADII;
    else { w = particleSpawnType::POINT; };
}
