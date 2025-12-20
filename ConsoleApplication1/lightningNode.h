#pragma once
#include <SDL3/SDL.h>

struct lightningNode {
    SDL_FPoint basePos;
    SDL_FPoint offset;

    float jitterPhase;
    float jitterAmplitude;

    float colorPhase;
};