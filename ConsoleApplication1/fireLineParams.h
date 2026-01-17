#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

struct fireLineParams {
    // length
    float minLength;
    float maxLength;
    float growSpeed;

    // direction (relative to straight up)
    float minAngle;
    float maxAngle;

    // endpoint sway (side-to-side motion)
    float swayAmplitude;    // pixels
    float swaySpeed;        // radians/sec

    // subtle length oscillation
    float lengthOscPct;     // 0.02–0.08
    float lengthOscSpeed;

    // color
    float colorSpeed;       // how fast colorT oscillates
    float colorStartMin;    // initial colorT range
    float colorStartMax;
};

inline void to_json(json& j, const fireLineParams& flc) { 
    j = json::object(); 

    j["minLength"] = flc.minLength;
    j["maxLength"] = flc.maxLength;
    j["growSpeed"] = flc.growSpeed;
    j["minAngle"] = flc.minAngle;
    j["maxAngle"] = flc.maxAngle;
    j["swayAmplitude"] = flc.swayAmplitude;
    j["swaySpeed"] = flc.swaySpeed;
    j["lengthOscPct"] = flc.lengthOscPct;
    j["lengthOscSpeed"] = flc.lengthOscSpeed;
    j["colorSpeed"] = flc.colorSpeed; 
    j["colorStartMin"] = flc.colorStartMin;
    j["colorStartMax"] = flc.colorStartMax;
}

inline void from_json(const json& j, fireLineParams& flc) {
    j.at("minLength").get_to(flc.minLength);
    j.at("maxLength").get_to(flc.maxLength);
    j.at("growSpeed").get_to(flc.growSpeed);
    j.at("minAngle").get_to(flc.minAngle);
    j.at("maxAngle").get_to(flc.maxAngle);
    j.at("swayAmplitude").get_to(flc.swayAmplitude);
    j.at("swaySpeed").get_to(flc.swaySpeed);
    j.at("lengthOscPct").get_to(flc.lengthOscPct);
    j.at("lengthOscSpeed").get_to(flc.lengthOscSpeed);
    j.at("colorSpeed").get_to(flc.colorSpeed); 
    j.at("colorStartMin").get_to(flc.colorStartMin);
    j.at("colorStartMax").get_to(flc.colorStartMax);
}

 
 
