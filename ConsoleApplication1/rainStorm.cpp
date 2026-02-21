#pragma once
#include "logManager.h"
#include "rainStorm.h"
#include "dropEmitter.h"
#include "rainStormSizeChanger.h"

const int MAXDROPSATONCE = 2000;

void rainStorm::update(float dt) {
    age += dt; 

    if (def.config.stormDuration > 0.0f && age > def.config.stormDuration) { return; }

    if (age < emitCutOff) {
        emitAccumulator += def.config.emitParams.dropsPerSecond * dt;
        int spawnCount = (int)emitAccumulator;
        emitAccumulator -= spawnCount;

        for (int i = 0; i < spawnCount && drops.size() < MAXDROPSATONCE; ++i) {
            drop d = rainDropEmitter::makeDrop(*this);
            drops.push_back(d);
        }
        logManager::logThis("emit drop");
    }
    else {
        emitAccumulator = 0;
        logManager::logThis("hit emit limit");
    }

    updateDrops(dt);
    animateSize(dt);
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
 
void rainStorm::updateDrops(float dt) {
    const auto& kill = actualKillParams;

    for (auto& d : drops) { 
        d.update(dt);

        // Use head of line for kill test
        SDL_FPoint p = d.start;

        if (isOutsideKillVolume(p, kill)) {
            if (age < emitCutOff) {
                resetDrop(d);
            }
        }
    }
}
 
void rainStorm::resetDrop(drop& d) {
    d = rainDropEmitter::makeDrop(*this);
}

bool rainStorm::isOutsideKillVolume(const SDL_FPoint& p, const rainKillParams& k) {
    switch (k.type) {
        case rainKillType::LOWER_Y:
            return p.y > k.lowerY;

        case rainKillType::RECTANGLE: {
            SDL_FRect r = k.rect.getSDLRect();

            float bottom = r.y + r.h;

            // Only consider killing once we're below the bottom of the box
            if (p.y <= bottom)
                return false;

            bool outsideHorizontally = (p.x < r.x) || (p.x > r.x + r.w);
            return outsideHorizontally;
        }
        case rainKillType::CIRCLE: {
            if (p.y <= k.center.y)
                return false;

            float dx = p.x - k.center.x;
            float dy = p.y - k.center.y;

            float distSq = dx * dx + dy * dy;
            float radiusSq = k.radius * k.radius;

            return distSq > radiusSq;
        }


        case rainKillType::ELLIPSE: {
            float nx = (p.x - k.center.x) / k.radiusX;
            float ny = (p.y - k.center.y) / k.radiusY;
            return (nx * nx + ny * ny) > 1.0f;
        }
    } 
    return true; 
}

void rainStorm::animateSize(float dt) {
    rainStormSizeAnimationSequence& aSeq = def.config.sizeAnimationSequence;

    if (!aSeq.animate) { return;}

    if (age > aSeq.sequence[aSeq.step].duration) { 
        aSeq.step++; 
    }
    
    
    if (aSeq.step >= aSeq.sequence.size()) { aSeq.step = 0; }

    changeSize(*this, dt);
}

 