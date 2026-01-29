#pragma once
#include "json.hpp"
#include "particleStormDef.h"
#include "particleOverrideParams.h"
#include "particle.h"

using json = nlohmann::ordered_json;

struct particleStorm {
	particleStormDef def;
    particleOverrides overrideParams = {};

    particleSpawnParams actualSpawnParams;
    particleMotionParams actualMotionParams;
    bool updateParams = true;

	float age = 0.0f; 
    float emitAccumulator = 0.0f;

    std::vector<particle> particles;
	void update(float t);
    void updateActualParams();
    void resolveSpawnOverride();
    void resolveMotionOverride();
    bool updateParticle(particle& p, float dt);
};

inline void to_json(json& j, const particleStorm& s) {
    j = json::object();

    j["def"] = s.def;
    j["overrideParams"] = s.overrideParams;
    j["actualSpawnParams"] = s.actualSpawnParams;
    j["actualMotionParams"] = s.actualMotionParams;
    j["updateParams"] = s.updateParams;
    j["age"] = s.age;
    j["emitAccumulator"] = s.emitAccumulator;
    j["particles"] = s.particles; 
}

inline void from_json(const json& j, particleStorm& s) {
    j.at("def").get_to(s.def);
    j.at("overrideParams").get_to(s.overrideParams);
    j.at("actualSpawnParams").get_to(s.actualSpawnParams);
    j.at("actualMotionParams").get_to(s.actualMotionParams);
    j.at("updateParams").get_to(s.updateParams);
    j.at("age").get_to(s.age); 
    j.at("emitAccumulator").get_to(s.emitAccumulator);
    s.particles = j.value("particles", std::vector<particle>{});
}