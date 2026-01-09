#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "fireStorm.h"
#include "fireStormDef.h"

class fireGenerator {
public:
    static fireStorm generateStorm(const fireStormDef& sourceDef, const fireStormSpawnParams& spawnParams, bool overrideSpawn);

private:
    static SDL_FPoint generateOrigin(const fireStormSpawnParams& spawn);

    static fire generateFire(const fireStormConfig& cfg, const SDL_FPoint& origin);
};
