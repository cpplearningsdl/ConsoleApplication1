#pragma once
#include "particleStorm.h" 
#include "particleEmitter.h"
#include "SDLLerp.h"

void particleStorm::resolveSpawnOverride() {
    if (overrideParams.overrideSpawn) {
        actualSpawnParams = overrideParams.spawn;
    }
    else {
        actualSpawnParams = def.config.spawnParams;
    } 
}
void particleStorm::resolveMotionOverride() {
    if (overrideParams.overrideMotion) {
        actualMotionParams = overrideParams.motion;
    }
    else {
        actualMotionParams = def.config.motionParams;
    }
};

void particleStorm::updateActualParams() {
    if (!updateParams) {
        return;
    }
    resolveSpawnOverride();
    resolveMotionOverride();
}

void particleStorm::update(float dt) {
    age += dt;
    updateActualParams();
    for (size_t i = 0; i < particles.size(); )
    {
        if (!updateParticle(particles[i], dt)) {
            particles[i] = particles.back();
            particles.pop_back();
        }
        else {
            ++i;
        }
    }

    emitAccumulator += dt * def.config.particlesPerSecond;

    while (emitAccumulator >= 1.0f) {
        particles.push_back(emitParticle(def.config, actualSpawnParams, actualMotionParams));
        emitAccumulator -= 1.0f;
    }
};

bool particleStorm::updateParticle(particle& p, float dt) {
    p.age += dt;
    if (!p.isAlive()) { 
        return false; 
    }

    particleMotionParams& motion = actualMotionParams;
    SDL_FPoint& origin = actualSpawnParams.origin;

    switch (motion.type) {

    case particleMotionType::FIXED_ANGLE:
    case particleMotionType::RANDOM_DIRECTION:
    case particleMotionType::OUTWARD_FROM_ORIGIN:
    case particleMotionType::INWARD_TOWARD_ORIGIN:
        p.position.x += p.velocity.x * dt;
        p.position.y += p.velocity.y * dt;
        break;

    case particleMotionType::ORBIT:
        p.orbitAngle += motion.angularSpeed * dt;
        p.position.x = origin.x + cosf(p.orbitAngle) * p.orbitRadius;
        p.position.y = origin.y + sinf(p.orbitAngle) * p.orbitRadius;
        break;

    case particleMotionType::SPIRAL_IN:
        p.orbitAngle += motion.angularSpeed * dt;
        p.orbitRadius -= motion.radialSpeed * dt;
        if (p.orbitRadius < 0.0f) p.orbitRadius = 0.0f;
        p.position.x = origin.x + cosf(p.orbitAngle) * p.orbitRadius;
        p.position.y = origin.y + sinf(p.orbitAngle) * p.orbitRadius;
        break;

    case particleMotionType::SPIRAL_OUT:
        p.orbitAngle += motion.angularSpeed * dt;
        p.orbitRadius += motion.radialSpeed * dt;
        p.position.x = origin.x + cosf(p.orbitAngle) * p.orbitRadius;
        p.position.y = origin.y + sinf(p.orbitAngle) * p.orbitRadius;
        break;
    }

    p.colorPhase += p.colorSpeed * dt;
    p.color = lerpColor(p.colorStart, p.colorEnd, p.colorPhase);

    // wrap into [0,1)
    if (p.colorPhase >= 1.0f) {
        p.colorPhase -= 1.0f;
    }

    //still alive so updated
    return true;
}
