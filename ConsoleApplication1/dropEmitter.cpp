#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <SDL3/SDL.h>
#include "SDL_FrectHelpers.h"
#include "windowSettings.h"
#include "rainStorm.h"
#include "dropEmitter.h"
#include "randomUtilityFunctions.h"

drop rainDropEmitter::makeDrop(const rainStorm& storm) {
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
    drop.end = { spawn.x + dir.x * length, spawn.y + dir.y * length };
    // Color
    drop.color = computeColor(storm, drop);

    return drop;
}

SDL_Color rainDropEmitter::computeColor(const rainStorm& storm, drop& d) {
    const auto& cp = storm.def.config.colors;

    bool useSecondary = randomFloat(0.0f, 1.0f) < cp.secondaryChance;

    if (useSecondary) {
        d.primary = false;
        return cp.secondary; 
    }
    else {
        d.primary = true;
        return cp.primary;
    }
}

SDL_FPoint rainDropEmitter::computeSpawnPoint(const rainStorm& storm) {
    const auto& sp = storm.actualSpawnParams;
    SDL_FPoint p{};

    switch (sp.type) {
        case rainSpawnTypeEnum::FULLSCREEN_TOPDOWN: {
            p.x = randomFloat(0.0f, logicalW);
            p.y = sp.spawnY;
            break;
        }

        case rainSpawnTypeEnum::RECTANGLE: {
            SDL_FRect rect = sp.rect.getSDLRect();
            p.x = randomFloat(rect.x, rect.x + rect.w);
            p.y = randomFloat(rect.y, rect.y + rect.h);
            break;
        }

        case rainSpawnTypeEnum::RADIUS: {
            // Uniform distribution in circle
            float angle = randomFloat(0.0f, 2.0f * M_PI);
            float r = sqrtf(randomFloat(0.0f, 1.0f)) * sp.radius;

            p.x = sp.center.x + cosf(angle) * r;
            p.y = sp.center.y + sinf(angle) * r;
            break;
        }

        case rainSpawnTypeEnum::ELLIPSE: {
            float angle = randomFloat(0.0f, 2.0f * M_PI);
            float r = sqrtf(randomFloat(0.0f, 1.0f));

            p.x = sp.center.x + cosf(angle) * r * sp.radiusX;
            p.y = sp.center.y + sinf(angle) * r * sp.radiusY;
            break;
        }
    }

    return p;
}
