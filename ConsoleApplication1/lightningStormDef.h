#pragma once
#include <string>
#include <SDL3/SDL.h>
#include "lightningStormConfig.h"

struct lightningStormDef {
    std::string id;

    lightningStormConfig config;

    // Defaults / relative anchors
    SDL_FPoint defaultStart{ 0, 0 };
    SDL_FPoint defaultEnd{ 0, 0 };
};