#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <SDL3/SDL.h>
#include "fireGenerator.h"
#include "randomUtilityFunctions.h"


fireStorm fireGenerator::generateStorm(const fireStormDef& sourceDef, const fireStormSpawnParams& spawnParams, bool overrideSpawn) {
    fireStorm storm;
     
    storm.def = sourceDef;
     
    if (overrideSpawn) {
        storm.def.config.spawnParams = spawnParams;
    }

    const fireStormSpawnParams& spawn = storm.def.config.spawnParams;

    int fireCount = randomInt(spawn.minFires, spawn.maxFires);

    storm.fires.reserve(fireCount);

    for (int i = 0; i < fireCount; ++i) {
        SDL_FPoint origin = generateOrigin(spawn);
        storm.fires.push_back(generateFire(storm.def.config, origin));
    }

    return storm;
};
 
SDL_FPoint fireGenerator::generateOrigin(const fireStormSpawnParams& spawn) {
    return { 0.0,0.0 };
};
 
fire fireGenerator::generateFire(const fireStormConfig& cfg, const SDL_FPoint& origin) {
    return { 0.0,0.0 };
};
