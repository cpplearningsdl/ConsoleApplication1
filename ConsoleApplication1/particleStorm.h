#pragma once
#include "json.hpp"
#include "particleStormDef.h"
#include "particleOverrideParams.h"
#include "particle.h" 
#include "timingMode.h"

using json = nlohmann::ordered_json;

struct particleStorm {
	particleStormDef def;
    particleOverrides overrideParams = {};

    particleSpawnParams actualSpawnParams;
    particleMotionParams actualMotionParams; 

    float nextMotionTime = 0.0f;
    int motionStep = 0;
    motionTimingMode timingMode = motionTimingMode::PER_STORM;
     
    std::vector<particle> particles;

	float age = 0.0f; 
    float emitAccumulator = 0.0f;  


	void update(float t);
    void updateActualParams();
    void resolveSpawnOverride();
    void resolveMotionOverride();
    void updateParticles(float dt);
    bool updateParticle(particle& p, float dt);
};

inline void to_json(json& j, const particleStorm& s) {
    j = json::object();

    j["def"] = s.def;
    j["overrideParams"] = s.overrideParams;
    j["actualSpawnParams"] = s.actualSpawnParams;
    j["actualMotionParams"] = s.actualMotionParams; 
    j["nextMotionTime"] = s.nextMotionTime;
    j["motionStep"] = s.motionStep;
    j["timingMode"] = s.timingMode; 
    j["particles"] = s.particles;
    j["age"] = s.age;
    j["emitAccumulator"] = s.emitAccumulator;

}

inline void from_json(const json& j, particleStorm& s) {
    j.at("def").get_to(s.def);
    j.at("overrideParams").get_to(s.overrideParams);
    j.at("actualSpawnParams").get_to(s.actualSpawnParams);
    j.at("actualMotionParams").get_to(s.actualMotionParams); 
    j.at("nextMotionTime").get_to(s.nextMotionTime);
    j.at("motionStep").get_to(s.motionStep);
    j.at("timingMode").get_to(s.timingMode); 
    s.particles = j.value("particles", std::vector<particle>{});
    j.at("age").get_to(s.age); 
    j.at("emitAccumulator").get_to(s.emitAccumulator);

}