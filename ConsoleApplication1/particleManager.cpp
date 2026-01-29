#pragma once
#include "SDL_FrectHelpers.h"
#include "particleManager.h"
#include "particleStorm.h" 
#include "particleStormDef.h"
#include "particleBatch.h"

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
        else { ++i; }
    }
    if (!storms.empty()) {
        buildParticleBatch();
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

void particleManager::buildParticleBatch(){
    // Count total particles
    size_t totalCount = 0;
    for (const auto& storm : storms)
    {
        totalCount += storm.particles.size();
    }

    // Ensure capacity (only grows)
    particleBatch.rects.reserve(totalCount);
    particleBatch.colors.reserve(totalCount);

    // Resize to exact size (no push_back)
    particleBatch.rects.resize(totalCount);
    particleBatch.colors.resize(totalCount);

    size_t index = 0;

    for (const auto& storm : storms)
    {
        for (const auto& p : storm.particles)
        {
            particleBatch.rects[index] = makeRectFromCenter(p.position, p.size);
            particleBatch.colors[index] = p.color;
            ++index;
        }
    }

  //  sortParticleBatchByColorInPlace(particleBatch);
    sortParticleBatchByColorInPlace(particleBatch);
    // Debug safety
    assert(index == totalCount);
}
