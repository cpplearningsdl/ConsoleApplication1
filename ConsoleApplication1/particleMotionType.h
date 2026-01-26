#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

enum class particleMotionType {
    FIXED_ANGLE,            // straight line at angle
    RANDOM_DIRECTION,       // straight line random
    OUTWARD_FROM_ORIGIN,    // radial outward
    INWARD_TOWARD_ORIGIN,   // radial inward
    ORBIT,                  // circle
    SPIRAL_IN,              // circle + radius shrinking
    SPIRAL_OUT              // circle + radius growing
};


inline void to_json(json& j, const particleMotionType& w) {
    switch (w) {
    case particleMotionType::FIXED_ANGLE:   j = "fixed_angle";   break;
    case particleMotionType::RANDOM_DIRECTION: j = "random_direction"; break;
    case particleMotionType::OUTWARD_FROM_ORIGIN:   j = "outward_from_origin";   break;
    case particleMotionType::INWARD_TOWARD_ORIGIN:  j = "inward_toward_origin";  break;
    case particleMotionType::ORBIT:   j = "orbit";   break;
    case particleMotionType::SPIRAL_IN:   j = "spiral_in";   break;
    case particleMotionType::SPIRAL_OUT:   j = "spiral_out";   break;
    default:
        j = "random_direction";
        break;
    }
}

inline void from_json(const json& j, particleMotionType& w) {
    const std::string s = j.get<std::string>();

    if (s == "fixed_angle")   w = particleMotionType::FIXED_ANGLE;
    else if (s == "random_direction") w = particleMotionType::RANDOM_DIRECTION;
    else if (s == "outward_from_origin")   w = particleMotionType::OUTWARD_FROM_ORIGIN;
    else if (s == "inward_toward_origin")  w = particleMotionType::INWARD_TOWARD_ORIGIN;
    else if (s == "orbit")  w = particleMotionType::ORBIT;
    else if (s == "spiral_in")  w = particleMotionType::SPIRAL_IN;
    else if (s == "spiral_out")  w = particleMotionType::SPIRAL_OUT;
    else { w = particleMotionType::RANDOM_DIRECTION; };
}
