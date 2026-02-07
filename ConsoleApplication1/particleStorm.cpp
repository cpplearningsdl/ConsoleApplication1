#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
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
    resolveSpawnOverride();
    resolveMotionOverride(); 
}

void particleStorm::updateParticles(float dt) {

    for (size_t i = 0; i < particles.size(); ) {
        if (!updateParticle(particles[i], dt)) {
            particles[i] = particles.back();
            particles.pop_back();
        }
        else {
            ++i;
        }
    }
}

void particleStorm::update(float dt) {
    age += dt; 
    if (timingMode == motionTimingMode::PER_STORM) {
        nextMotionTime += dt;
        if (nextMotionTime > def.config.nextMotions.steps[motionStep].duration) {
            auto& steps = def.config.nextMotions.steps;
            motionStep++;
            if (motionStep >= steps.size()) {
                motionStep = 0;
                nextMotionTime = 0.0f;
            }
            nextMotionTime = 0.0f;
            actualMotionParams = steps[motionStep];

            float speed = randomFloat(def.config.particleCfg.speedMin, def.config.particleCfg.speedMax); 
            //init new motion here
            for (size_t i = 0; i < particles.size(); i++) {
                particles[i].currentStep = motionStep;
                particles[i].nextMotionTime = 0.0f;
                initParticleMotion(particles[i], steps[motionStep], actualSpawnParams, speed);
            }
        } 
        updateParticles(dt);
    }
    else if (timingMode == motionTimingMode::PER_PARTICLE){
        auto& steps = def.config.nextMotions.steps;
        for (size_t i = 0; i < particles.size();){
            particles[i].nextMotionTime += dt;
            if (particles[i].nextMotionTime >= steps[particles[i].currentStep].duration) {
                particles[i].currentStep++;
                particles[i].nextMotionTime = 0.0f;
                if (particles[i].currentStep >= steps.size()) {
                    particles[i].currentStep = 0;
                    particles[i].nextMotionTime = 0.0f;
                } 
                //init new motion here
                float speed = randomFloat(def.config.particleCfg.speedMin, def.config.particleCfg.speedMax);
                initParticleMotion(particles[i], def.config.nextMotions.steps[particles[i].currentStep], actualSpawnParams, speed);
            } 
            i++;
        }
        updateParticles(dt);
    }

    if (particles.size() >= def.config.maxParticles) { return; }
    
    emitAccumulator += dt * def.config.particlesPerSecond;

     
    while (emitAccumulator >= 1.0f && def.config.emitLength > age) {
        particles.push_back(emitParticle(def.config, actualSpawnParams, def.config.nextMotions.steps[0]));//add option to start at storms step
        emitAccumulator -= 1.0f;
    }
};

bool particleStorm::updateParticle(particle& p, float dt) {
    p.age += dt;
    if (!p.isAlive()) { 
        return false; 
    } 

    particleMotionParams& motion = def.config.nextMotions.steps[p.currentStep];
    SDL_FPoint& origin = actualSpawnParams.origin;

    switch (motion.type) {
    case particleMotionType::PAUSE:
        break;
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
        if (p.orbitRadius < 7.0f) {
            p.orbitRadius = 7.0f;
        }
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
    float t = (sinf(p.colorPhase * 2.0f * M_PI) + 1.0f) * 0.5f;
   // p.color = lerpColor(p.colorStart, p.colorEnd, p.colorPhase);
    p.color = lerpColor(p.colorStart, p.colorEnd, t);
    // wrap into [0,1)
    if (p.colorPhase >= 1.0f) {
        p.colorPhase -= 1.0f;
    }

    //still alive so updated
    return true;
}
