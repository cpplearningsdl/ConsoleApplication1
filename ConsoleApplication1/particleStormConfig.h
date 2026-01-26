#pragma once
#include "json.hpp"
#include "particleSpawnParams.h" 
#include "particleMotionParams.h"
#include "particleConfig.h"

using json = nlohmann::ordered_json;

struct particleStormConfig {
	float stormDuration = 2.0f;
    float particlesPerSecond = 50.0f;
    particleSpawnParams spawnParams; 
    particleMotionParams motionParams;
    particleConfig particleCfg;
};

inline void to_json(json& j, const particleStormConfig& c) {
    j = json::object();

    j["stormDuration"] = c.stormDuration; 
    j["particlesPerSecond"] = c.particlesPerSecond;
    j["spawnParams"] = c.spawnParams;
    j["motionParams"] = c.motionParams;
    j["particleCfg"] = c.particleCfg;
}

inline void from_json(const json& j, particleStormConfig& c) {
    c = particleStormConfig{};

    if (j.contains("stormDuration"))
        c.stormDuration = j.at("stormDuration").get<float>();

    if (j.contains("particlesPerSecond"))
        c.particlesPerSecond = j.at("particlesPerSecond").get<float>();
     
    if (j.contains("spawnParams"))
        c.spawnParams = j.at("spawnParams").get<particleSpawnParams>();
     

    if (j.contains("motionParams"))
        c.motionParams = j.at("motionParams").get<particleMotionParams>();

    if (j.contains("particleCfg"))
        c.particleCfg = j.at("particleCfg").get<particleConfig>();

    c.stormDuration = std::max(0.0f, c.stormDuration);
}