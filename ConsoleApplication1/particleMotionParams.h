#pragma once
#include "json.hpp" 
#include "particleMotionType.h"

struct particleMotionParams {
    particleMotionType type = particleMotionType::FIXED_ANGLE;
    float duration = 0.0f;
    float angleDegrees = 0.0f;     // FIXED_ANGLE
    float spreadDegrees = 0.0f;    // applies to all linear modes

    float angularSpeed = 2.0f;     // ORBIT / SPIRAL
    float radialSpeed = 20.0f;     // SPIRAL
};


inline void to_json(json& j, const particleMotionParams& pcr) {
    j = json::object();

    j["type"] = pcr.type;
    j["duration"] = pcr.duration;
    j["angleDegrees"] = pcr.angleDegrees;
    j["spreadDegrees"] = pcr.spreadDegrees;

    j["angularSpeed"] = pcr.angleDegrees;
    j["radialSpeed"] = pcr.spreadDegrees;
}

inline void from_json(const json& j, particleMotionParams& pcr) {
    j.at("type").get_to(pcr.type);
    j.at("duration").get_to(pcr.duration);
    j.at("angleDegrees").get_to(pcr.angleDegrees);
    j.at("spreadDegrees").get_to(pcr.spreadDegrees);

    j.at("angularSpeed").get_to(pcr.angularSpeed);
    j.at("radialSpeed").get_to(pcr.radialSpeed);
}