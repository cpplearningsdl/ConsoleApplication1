#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::ordered_json;

enum class rainSpawnTypeEnum {
    FULLSCREEN_TOPDOWN,   // spawn across screen width, falls to a computed lowerY
    RECTANGLE,            // finite box
    RADIUS,               // circular area
    ELLIPSE               // elliptical area
};

inline void to_json(json& j, const enum class rainSpawnTypeEnum& rst) {
    switch (rst) {
    case rainSpawnTypeEnum::FULLSCREEN_TOPDOWN:   j = "FULLSCREEN_TOPDOWN";   break;
    case rainSpawnTypeEnum::RECTANGLE: j = "RECTANGLE"; break;
    case rainSpawnTypeEnum::RADIUS: j = "RADIUS"; break; 
    case rainSpawnTypeEnum::ELLIPSE: j = "ELLIPSE"; break;
    default:
        j = "NONE";
        break;
    }
}

inline void from_json(const json& j, rainSpawnTypeEnum& t) {
    const std::string s = j.get<std::string>();

    if (s == "NONE")                        t = rainSpawnTypeEnum::FULLSCREEN_TOPDOWN;
    else if (s == "FULLSCREEN_TOPDOWN")       t = rainSpawnTypeEnum::FULLSCREEN_TOPDOWN;
    else if (s == "RECTANGLE")              t = rainSpawnTypeEnum::RECTANGLE;
    else if (s == "RADIUS")                 t = rainSpawnTypeEnum::RADIUS;
    else if (s == "ELLIPSE")                 t = rainSpawnTypeEnum::ELLIPSE;
}
