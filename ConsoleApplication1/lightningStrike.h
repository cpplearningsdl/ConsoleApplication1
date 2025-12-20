#pragma once
#include <vector>
#include "lightningNode.h"
#include "lightningSegment.h"

struct lightningStrike {
    std::vector<lightningNode> nodes;
    std::vector<lightningSegment> segments;

    SDL_FPoint start;
    SDL_FPoint end;

    float age = 0.0f;
    float lifetime = 0.2f;
    float intensity = 1.0f;

    float rebuildTimer = 0.0f;
    float rebuildInterval = 0.0f;

    bool persistent = false;
    bool dead = false;

    uint32_t seed;
};
