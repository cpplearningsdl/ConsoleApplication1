#pragma once
#include <SDL3/SDL.h>
#include "rainStorm.h"
#include "dropEmitter.h"
#include "randomUtilityFunctions.h"

drop rainDropEmitter::makeDrop(const rainStorm& storm)
{
    const auto& cfg = storm.def.config;

    drop drop{};

    // Spawn point
    SDL_FPoint spawn = computeSpawnPoint(storm);

    // Wind angle
    float angle = storm.wind.currentAngleDeg + randomFloat(-cfg.windParams.angleVariance, cfg.windParams.angleVariance);

    float rad = degToRad(angle);
    SDL_FPoint dir = { cosf(rad), sinf(rad) };

    // Speed
    float speed = randomFloat(cfg.velocityParams.min, cfg.velocityParams.max);

    drop.velocity = { dir.x * speed, dir.y * speed };

    // Length
    float length = randomFloat(cfg.sizeParams.lengthMin, cfg.sizeParams.lengthMax);

    drop.start = spawn;
    drop.end = { spawn.x - dir.x * length, spawn.y - dir.y * length };

    // Color
    drop.color = computeColor(storm);

    return drop;
}

SDL_Color rainDropEmitter::computeColor(const rainStorm& storm) {
    const auto& cp = storm.def.config.colors;

    bool useSecondary = randomFloat(0.0f, 1.0f) < cp.secondaryChance;

    if (useSecondary) {
        return cp.secondary; 
    }
    else {
        return cp.primary;
    }
}
