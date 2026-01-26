#pragma once
#include "particleManager.h"
#include "particleStorm.h" 
#include "particleStormDef.h"

particleManager::particleManager() {

};
particleManager::~particleManager() {
	storms.clear();
};

void particleManager::update(float dt) {
    for (auto& storm : storms) {
        storm.update(dt);
    }
    for (size_t i = 0; i < storms.size(); ) {
        if (storms[i].age > storms[i].def.config.stormDuration) {
            storms[i] = storms.back();
            storms.pop_back();
        }
    }

}
void particleManager::addParticleStorm(const std::string& id) {
    storms.emplace_back();
    auto& s = storms.back();

    s.def = defaults.get(id);

    const float expected = s.def.config.particlesPerSecond * s.def.config.stormDuration;

    s.particles.reserve(static_cast<size_t>(std::ceil(expected * 1.10f)));
}

void particleManager::addParticleStorm(const std::string id, particleSpawnParams& p) {
	particleStorm s;
	s.def = defaults.get(id);


};