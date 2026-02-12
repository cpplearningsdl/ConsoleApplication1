#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "rainStorm.h"

class rainDropEmitter {
public:
    static drop makeDrop(const rainStorm& storm);

private:
    static SDL_FPoint computeSpawnPoint(const rainStorm& storm);
    static SDL_Color computeColor(const rainStorm& storm);
};