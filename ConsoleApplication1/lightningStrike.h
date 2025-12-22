#pragma once
#include <vector>
#include "lightningNode.h"
#include "lightningSegment.h"
#include "lightningGeneratorConfig.h"

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

    // --- rotational motion ---
    bool rotateAroundEnd = false;
    float rotationAngle = 0.0f;
    float rotationSpeed = 0.0f;      // radians per second
    float rotationRadius = 0.0f;

    uint32_t seed;
    lightningGeneratorConfig genCfg;
};
