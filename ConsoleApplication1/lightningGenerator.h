#pragma once
#include "lightningStrike.h"
#include "lightningGeneratorConfig.h"

class lightningGenerator {
public:
    static lightningStrike generate(SDL_FPoint start, SDL_FPoint end, const lightningGeneratorConfig& cfg, uint32_t seed);
};