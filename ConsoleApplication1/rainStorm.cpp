#pragma once
#include "rainStorm.h"
#include "dropEmitter.h"

const int MAXDROPSATONCE = 2000;

void rainStorm::update(float dt) {
    age += dt; 

    if (def.config.stormDuration > 0.0f && age > def.config.stormDuration) { return; }

    emitAccumulator += def.config.spawnParams.dropsPerSecond * dt; 
    int spawnCount = (int)emitAccumulator;
    emitAccumulator -= spawnCount;

    for (int i = 0; i < spawnCount && drops.size() < MAXDROPSATONCE; ++i) {
        drop d = rainDropEmitter::makeDrop(*this);
        drops.push_back(d);
    }

    updateDrops(dt);
};
void rainStorm::updateActualParams() {
	resolveSpawnOverride();
};

void rainStorm::resolveSpawnOverride() {
    if (overrideParams.overrideSpawn) {
        actualSpawnParams = overrideParams.spawnOverrides;
    }
    else {
        actualSpawnParams = def.config.spawnParams;
    }
};

void rainStorm::updateDrops(float dt)
{
    const auto& kill = def.config.killParams;

    for (auto& d : drops) {

        d.update(dt);

        // Use head of line for kill test
        SDL_FPoint p = d.start;

        if (isOutsideKillVolume(p, kill)) {
            resetDrop(d);
        }
    }
}

bool rainStorm::updateDrop(drop& p, float dt) {
 
};

void rainStorm::resetDrop(drop& d) {
    d = rainDropEmitter::makeDrop(*this);
}

bool rainStorm::isOutsideKillVolume(const SDL_FPoint& p, const rainKillParams& k) {
    switch (k.type) {
        case rainKillType::LOWER_Y:
            return p.y > k.lowerY;

        case rainKillType::RECTANGLE:
            return !(p.x >= k.rect.x && p.x <= k.rect.x + k.rect.w && p.y >= k.rect.y && p.y <= k.rect.y + k.rect.h);

        case rainKillType::CIRCLE: {
            float dx = p.x - k.center.x;
            float dy = p.y - k.center.y;
            float distSq = dx * dx + dy * dy;
            return distSq > (k.radius * k.radius);
        }

        case rainKillType::ELLIPSE: {
            float nx = (p.x - k.center.x) / k.radiusX;
            float ny = (p.y - k.center.y) / k.radiusY;
            return (nx * nx + ny * ny) > 1.0f;
        }
    } 
    return true; 
}
