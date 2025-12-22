#pragma once
#include <random>
#include "lightningStrike.h"
#include "lightningGeneratorConfig.h"

class lightningGenerator {
public:
    static lightningStrike generate(SDL_FPoint start, SDL_FPoint end, const lightningGeneratorConfig& cfg, uint32_t seed);
    static void rebuild(SDL_FPoint start, SDL_FPoint end, std::vector<lightningNode>& nodes, std::vector<lightningSegment>& segments,  const lightningGeneratorConfig& cfg, std::mt19937& rng);
};