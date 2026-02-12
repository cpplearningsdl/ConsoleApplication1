#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

enum class rainKillType {
    LOWER_Y,     // classic line
    RECTANGLE,
    CIRCLE,
    ELLIPSE
};

inline void to_json(json& j, const enum class rainKillType& rkt) {
    switch (rkt) {
    case rainKillType::LOWER_Y:   j = "LOWER_Y";   break;
    case rainKillType::RECTANGLE: j = "RECTANGLE"; break;
    case rainKillType::CIRCLE:    j = "CIRCLE"; break;
    case rainKillType::ELLIPSE:   j = "ELLIPSE"; break;
    default:
        j = "LOWER_Y";
        break;
    }
}

inline void from_json(const json& j, rainKillType& t) {
    const std::string s = j.get<std::string>();

    if (s == "LOWER_Y")             t = rainKillType::LOWER_Y;
    else if (s == "RECTANGLE")      t = rainKillType::RECTANGLE;
    else if (s == "CIRCLE")         t = rainKillType::CIRCLE;
    else if (s == "ELLIPSE")        t = rainKillType::ELLIPSE; 
}