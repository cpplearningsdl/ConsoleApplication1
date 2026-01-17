#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <SDL3/SDL.h>
#include "fireGenerator.h" 
#include "randomUtilityFunctions.h"
#include "SDLLerp.h"
 
float UP = -1.57079632679f;

void fireGenerator::generateStorm(fireStorm& s, int fireCount) {
    for (int i = 0; i < fireCount; ++i) {
        SDL_FPoint origin = generateOrigin(s.def.config.spawnParams);
        s.fires.push_back(generateFire(s.def.config, origin));
    }
};
 
SDL_FPoint fireGenerator::generateOrigin(const fireStormSpawnParams& spawn) {
    SDL_FPoint p{ 0.0f, 0.0f };

    switch (spawn.spawnType) {
    case fireSpawnTypeEnum::POINT:
        p = spawn.spawnPoint;
        break;

    case fireSpawnTypeEnum::RADIUS: {
        float angle = randomFloat(0.0f, 6.283185307f); // 2pi
        float radius = randomFloat(0.0f, spawn.spawnRadius);

        p.x = spawn.spawnPoint.x + std::cos(angle) * radius;
        p.y = spawn.spawnPoint.y + std::sin(angle) * radius;
        break;
    }

    case fireSpawnTypeEnum::RECTANGLE:
        p.x = randomFloat(spawn.topLeft.x, spawn.bottomRight.x);
        p.y = randomFloat(spawn.topLeft.y, spawn.bottomRight.y);
        break;
    }

    return p;
}

std::vector<fireLine> fireGenerator::generateFireLines(const SDL_FPoint& origin, int count, const fireLineParams& cfg, float halfWidth, float size) {
    std::vector<fireLine> lines;
    lines.reserve(count);
     

    for (int i = 0; i < count; ++i) {
        fireLine line{};

        float xOffset = randomFloat(-halfWidth, halfWidth);

        line.start = { origin.x + xOffset, origin.y};
        line.end = origin;

        float angle = randomFloat(cfg.minAngle, cfg.maxAngle);
        line.dir = { std::sin(angle), -std::cos(angle) };

        line.targetLength = randomFloat(cfg.minLength, cfg.maxLength);
        line.currentLength = 0.0f;

        line.swayPhase = randomFloat(0.0f, 6.2831853f);
        line.lengthPhase = randomFloat(0.0f, 6.2831853f);

        line.colorT = randomFloat(cfg.colorStartMin, cfg.colorStartMax);
        line.colorDir = randomBool() ? 1.0f : -1.0f;

        lines.push_back(line);
    }

    return lines;
}


fire fireGenerator::generateFire(const fireStormConfig& cfg, const SDL_FPoint& origin){
    fire f;
    f.origin = origin;

    const float pixelScale = 100.0f;

    const float size = randomFloat(cfg.sizeParams.sizeMin, cfg.sizeParams.sizeMax);

    const float halfWidth = size * cfg.sizeParams.baseWidthMultiplier * 0.5f;


    // ---------------- PRIMARY LINES ----------------
    int primaryCount = randomInt(cfg.sizeParams.primaryLinesMin, cfg.sizeParams.primaryLinesMax);

    float primaryBaseLength = size * pixelScale;

    f.primary = generateFireLines(origin, primaryCount, cfg.fireLineParams.primary, halfWidth, size);

    // ---------------- SECONDARY LINES ----------------
    int secondaryCount = randomInt(cfg.sizeParams.secondaryLinesMin, cfg.sizeParams.secondaryLinesMax);

    float secondaryBaseLength = primaryBaseLength * 0.6f;

    f.secondary = generateFireLines(origin, secondaryCount,cfg.fireLineParams.secondary, halfWidth, size);

    // ---------------- EMBERS (UNCHANGED) ----------------
    int emberCount =  0;

    for (int i = 0; i < emberCount; ++i) {
        emberParticle e;
        e.pos = origin;
        e.velocity = {
            randomFloat(-0.4f, 0.4f) * size * pixelScale,
            randomFloat(-1.2f, -0.6f) * size * pixelScale
        };
        e.lifetime = randomFloat(0.8f, 1.6f);
        e.color = cfg.emberParams.emberColorMin;
        e.movement = cfg.emberParams.emberMovement;
        f.embers.push_back(e);
    }

    return f;
}
 
emberParticle fireGenerator::generateEmber(const fireStormEmberParams& emberCfg, const SDL_FPoint& origin) {
    emberParticle e;
    e.pos = origin; 
    e.velocity = { randomFloat(-0.4f, 0.4f), randomFloat(-1.2f, -0.6f) };
    e.lifetime = randomFloat(0.8f, 2.4f);
    e.color = emberCfg.emberColorMin;
    e.movement = emberCfg.emberMovement;
    return e;
}