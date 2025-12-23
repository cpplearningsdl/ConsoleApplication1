#pragma once
#include <vector>
#include <random>
#include "lightningNode.h"
#include "lightningSegment.h"
#include "lightningGeneratorConfig.h"
#include "lightningMovementEnum.h"

struct lightningStrike {
    std::vector<lightningNode> nodes;
    std::vector<lightningSegment> segments;

    SDL_FPoint start;
    SDL_FPoint end;
     
    float age = 0.0f;
    float lifetime = 0.2f;
    float intensity = 1.0f;//add to cfg

    SDL_FPoint walkVelocity{ 0, 0 };
    float walkRebuildInterval = 0.0f;
    float walkRebuildTimer = 0.0f;

    lightningMovementEnum movementMode = lightningMovementEnum::NONE;
    SDL_FPoint velocity{ 0, 0 };

    SDL_FPoint targetPoint{ 0, 0 };   // for MoveTowardPoint
    float targetSpeed = 0.0f;

    // Generation intent
    float strikeAngle = 0.0f;        // radians
    bool hasStrikeAngle = false;

    float rebuildTimer = 0.0f;
    float rebuildInterval = 0.0f;

    bool persistent = false;
    bool dead = false;

    // --- rotational motion ---
    bool rotateAroundEnd = false;
    float rotationAngle = 0.0f;
    float rotationSpeed = 0.0f;      // radians per second
    float rotationRadius = 0.0f;

    std::mt19937 rng;
    uint32_t seed;
    lightningGeneratorConfig genCfg;
};
