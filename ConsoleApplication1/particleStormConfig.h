#pragma once
#include "json.hpp"
#include "particleSpawnParams.h" 
#include "particleMotionParams.h"
#include "particleConfig.h"
#include "particleMotionSequence.h"

using json = nlohmann::ordered_json;

struct particleStormConfig {
	float stormDuration = 2.0f;
    float particlesPerSecond = 50.0f;
    int maxParticles = 10000;
    float emitLength = 0.0f;
    //timing mode?
    particleSpawnParams spawnParams; 
    particleMotionParams motionParams;
    particleConfig particleCfg; 
    particleMotionSequence nextMotions;
};

inline void to_json(json& j, const particleStormConfig& c) {
    j = json::object();

    j["stormDuration"] = c.stormDuration; 
    j["particlesPerSecond"] = c.particlesPerSecond;
    j["maxParticles"] = c.maxParticles;
    j["spawnParams"] = c.spawnParams;
    j["motionParams"] = c.motionParams;
    j["particleCfg"] = c.particleCfg;
    j["nextMotions"] = c.nextMotions;
    j["emitLength"] = c.emitLength;
}

inline void from_json(const json& j, particleStormConfig& c) {
    c = particleStormConfig{};

    if (j.contains("stormDuration"))
        c.stormDuration = j.at("stormDuration").get<float>();

    if (j.contains("particlesPerSecond"))
        c.particlesPerSecond = j.at("particlesPerSecond").get<float>();

    if (j.contains("maxParticles"))
        c.maxParticles = j.at("maxParticles").get<int>();
     
    if (j.contains("spawnParams"))
        c.spawnParams = j.at("spawnParams").get<particleSpawnParams>();
     

    if (j.contains("motionParams"))
        c.motionParams = j.at("motionParams").get<particleMotionParams>();

    if (j.contains("particleCfg"))
        c.particleCfg = j.at("particleCfg").get<particleConfig>();
     
    if (j.contains("nextMotions"))
        c.nextMotions = j.at("nextMotions").get< particleMotionSequence>();
     
    if (j.contains("emitLength"))
        c.emitLength = j.at("emitLength").get<float>();


    c.stormDuration = std::max(0.0f, c.stormDuration);
}