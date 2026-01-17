#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::ordered_json;


enum class fireSpawnTypeEnum {
    NONE,
    ANYWHEREONSCREEN,
    RECTANGLE,
    RADIUS,
    POINT
};

inline void to_json(json& j, const enum class fireSpawnTypeEnum& fst) {
    switch (fst) {
    case fireSpawnTypeEnum::NONE:   j = "NONE";   break;
    case fireSpawnTypeEnum::ANYWHEREONSCREEN: j = "ANYWHEREONSCREEN"; break;
    case fireSpawnTypeEnum::RECTANGLE: j = "RECTANGLE"; break;
    case fireSpawnTypeEnum::RADIUS: j = "RADIUS"; break;
    case fireSpawnTypeEnum::POINT: j = "POINT"; break;
    default:
        j = "NONE"; 
        break;
    }
}

inline void from_json(const json& j, fireSpawnTypeEnum& t){
    const std::string s = j.get<std::string>();

    if (s == "NONE")                        t = fireSpawnTypeEnum::NONE;
    else if (s == "ANYWHEREONSCREEN")       t = fireSpawnTypeEnum::ANYWHEREONSCREEN;
    else if (s == "RECTANGLE")              t = fireSpawnTypeEnum::RECTANGLE;
    else if (s == "RADIUS")                 t = fireSpawnTypeEnum::RADIUS;
    else if (s == "POINT")                 t = fireSpawnTypeEnum::POINT;
}
