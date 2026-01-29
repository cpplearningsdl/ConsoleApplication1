#pragma once
#include <SDL3/SDL.h>
#include "SDL_Color_Range.h" 
#include "particleStorm.h"
#include "randomUtilityFunctions.h"

inline particle emitParticle(const particleStormConfig& cfg, const particleSpawnParams& spawn, const particleMotionParams& motion) {

    particle p;

    // --------------------
    // Lifetime & size
    // --------------------
    p.age = 0.0f;
    p.lifetime = randomFloat(cfg.particleCfg.lifetimeMin, cfg.particleCfg.lifetimeMax);
    //----
    //size & speed
    //
    p.size = randomFloat(cfg.particleCfg.sizeMin, cfg.particleCfg.sizeMax);
    float speed = randomFloat(cfg.particleCfg.speedMin, cfg.particleCfg.speedMax);
    // --------------------
    // Color selection
    // --------------------
    bool useSecondary = randomFloat(0.0f, 1.0f) < cfg.particleCfg.secondaryColorChance;

    if (useSecondary) {
        p.colorStart = randomColorInRange(cfg.particleCfg.secondaryColor);
        p.colorEnd = randomColorInRange(cfg.particleCfg.secondaryColor);
    }
    else {
        p.colorStart = randomColorInRange(cfg.particleCfg.primaryColor);
        p.colorEnd = randomColorInRange(cfg.particleCfg.primaryColor);
    }

    p.color = p.colorStart;
    p.colorPhase = cfg.particleCfg.colorPhase;
    p.colorSpeed = cfg.particleCfg.colorSpeed;

    // --------------------
    // Spawn position
    // --------------------
    float angle = randomFloat(0.0f, 2.0f * 3.1415926535f);
    float radius = 0.0f;

    switch (spawn.type)
    {
    case particleSpawnType::POINT:
        p.position = spawn.origin;
        break;

    case particleSpawnType::RANDOM_WITHIN_RADIUS:
        radius = randomFloat(0.0f, spawn.radiusOuter);
        p.position.x = spawn.origin.x + cosf(angle) * radius;
        p.position.y = spawn.origin.y + sinf(angle) * radius;
        break;

    case particleSpawnType::RANDOM_OUTSIDE_RADIUS:
        radius = randomFloat(spawn.radiusOuter, spawn.radiusOuter * 2.0f);
        p.position.x = spawn.origin.x + cosf(angle) * radius;
        p.position.y = spawn.origin.y + sinf(angle) * radius;
        break;

    case particleSpawnType::RANDOM_BETWEEN_RADII:
        radius = randomFloat(spawn.radiusInner, spawn.radiusOuter);
        p.position.x = spawn.origin.x + cosf(angle) * radius;
        p.position.y = spawn.origin.y + sinf(angle) * radius;
        break;
    }

    // --------------------
    // Motion initialization
    // --------------------
    float angleRad = 0.0f;

    switch (motion.type)
    {
    case particleMotionType::FIXED_ANGLE:
        angleRad = degToRad(motion.angleDegrees +
            randomFloat(-motion.spreadDegrees, motion.spreadDegrees));
        break;

    case particleMotionType::RANDOM_DIRECTION:
        angleRad = randomFloat(0.0f, 2.0f * 3.1415926535f);
        break;

    case particleMotionType::OUTWARD_FROM_ORIGIN:
        angleRad = atan2f(
            p.position.y - spawn.origin.y,
            p.position.x - spawn.origin.x);
        break;

    case particleMotionType::INWARD_TOWARD_ORIGIN:
        angleRad = atan2f(
            spawn.origin.y - p.position.y,
            spawn.origin.x - p.position.x);
        break;

    case particleMotionType::ORBIT:
    case particleMotionType::SPIRAL_IN:
    case particleMotionType::SPIRAL_OUT:
        p.orbitRadius = hypotf(
            p.position.x - spawn.origin.x,
            p.position.y - spawn.origin.y
        );

        p.orbitAngle = atan2f(
            p.position.y - spawn.origin.y,
            p.position.x - spawn.origin.x
        );

        p.velocity = { 0.0f, 0.0f }; 

        return p;
    }

    // --------------------
    // Linear velocity
    // --------------------
    p.velocity.x = cosf(angleRad) * speed;
    p.velocity.y = sinf(angleRad) * speed;
 
    return p;
}

