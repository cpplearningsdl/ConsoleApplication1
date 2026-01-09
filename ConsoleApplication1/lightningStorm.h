#pragma once
#include <SDL3/SDL.h>
#include "lightningStormConfig.h"
#include "lightningStormDef.h"

struct lightningStorm { 
    const lightningStormDef* def = nullptr;

    SDL_FPoint start;
    SDL_FPoint end;
    SDL_FPoint target;

    float age = 0.0f;
    float spawnTimer = 0.0f;
    int strikesSpawned = 0;
    bool finished = false;
};