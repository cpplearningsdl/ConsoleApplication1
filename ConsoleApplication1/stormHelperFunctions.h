#pragma once
#include <random>
#include "randomUtilityFunctions.h"
#include "logManager.h"
#include "lightningStorm.h"
#include "lightningStrike.h"
#include "lightningGenerator.h"
#include "lightningManagerHelperFunctions.h"
#include "lightningPlacementModeEnum.h"
#include "windowSettings.h"

void updateStormAge(std::vector<lightningStorm>& storms, float dt) {
    for (auto& storm : storms) {
        storm.age += dt;
        storm.spawnTimer -= dt;
         
        if (storm.age >= storm.def->config.stormDuration) {
            storm.finished = true;
        }
    }
}

static void setupMoveTowardTarget(lightningStrike& strike, float speed) {
    SDL_FPoint dir{
        strike.targetPoint.x - strike.start.x,
        strike.targetPoint.y - strike.start.y
    };

    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len < 0.0001f) {
        strike.movementMode = lightningMovementEnum::NONE;
        strike.moveDir = { 0.0f, 0.0f };
        strike.moveSpeed = 0.0f;
        return;
    }

    dir.x /= len;
    dir.y /= len;

    strike.moveDir = dir;
    strike.moveSpeed = speed;
    strike.movementMode = lightningMovementEnum::MOVETOWARDPOINT;
}



void spawnStrikeFromStorm(lightningStorm& storm, std::vector<lightningStrike>& strikes, float dt) {
    const auto& cfg = storm.def->config; 
    std::mt19937 rng(gRng); 

    SDL_FPoint start = storm.start;
    SDL_FPoint end = storm.end;

    switch (cfg.placement) {
    case lightningPlacementMode::RANDOMONSCREEN:
        start = randomPointOnScreen(logicalW, logicalH, rng);
        end = randomPointOnScreen(logicalW, logicalH, rng);
        break;
    case lightningPlacementMode::RANDOMSCREENVERTICALFROMTOP:
        start = randomVerticalFromTop(logicalW, rng);
        end = randomVerticalBottom(start.x, logicalW, logicalH, cfg.maxHorizontalDelta, rng);
        break;
    case lightningPlacementMode::RANDOMONSCREENVERTICAL:
        start = randomVerticalTop(logicalW, logicalH, rng);
        end = randomVerticalBottom(start, logicalW, logicalH, 200.0f, cfg.maxHorizontalDelta, rng);
        break;
    case lightningPlacementMode::RADIUSFROMPOINT:
        start = randomPointInRadius(storm.start, cfg.radius, rng);
        end = randomPointInRadius(storm.start, cfg.radius, rng);
        break;
    case lightningPlacementMode::GOTOPOINT:
        end = calculateEndFromTarget(storm.start, storm.target, cfg.maxStrikeHeight);
        break;

    case lightningPlacementMode::FIXEDENDPOINTS:
    default:
        break;
    }

    lightningStrike strike = lightningGenerator::generate(start, end, cfg.generator, rng(), storm.target);

    if (cfg.placement == lightningPlacementMode::GOTOPOINT) {
        strike.start = start;
        strike.targetPoint = storm.target;
        strike.end = calculateEndFromTarget(strike.start, strike.targetPoint, cfg.maxStrikeHeight);
        setupMoveTowardTarget(strike, cfg.moveSpeed);
    }
    else {
        strike.start = start;
        strike.end = end;
    }
        

    strike.lifetime = cfg.strikeLifetime;
    //  strike.intensity = not added yet..
    strike.persistent = cfg.persistentStrike;

    strike.walkVelocity = cfg.walkVelocity;
    strike.walkRebuildInterval = cfg.walkRebuildInterval;
    strike.walkRebuildTimer = 0.0f;

    strike.rotateAroundEnd = cfg.rotateStrikeStart;
    strike.rotationSpeed = cfg.rotationSpeed;
    strike.rotationRadius = cfg.rotationRadius;
    strike.rebuildInterval = cfg.rebuildInterval;

    strikes.push_back(std::move(strike));
}

void tryToSpawnStrikes(std::vector<lightningStorm>& storms, std::vector<lightningStrike>& strikes, float dt) {
    for (auto& storm : storms) {
        if (!storm.finished && storm.spawnTimer <= 0.0f && storm.strikesSpawned < storm.def->config.maxStrikes) {
            storm.spawnTimer = storm.def->config.strikeInterval;

            spawnStrikeFromStorm(storm, strikes, dt);
            storm.strikesSpawned++;
        }
    }

}

static void updateMoveTowardTarget(lightningStrike& strike, float dt, bool& updateRebuild) {
    if (strike.movementMode != lightningMovementEnum::MOVETOWARDPOINT) {
        updateRebuild = false;
        return;
    }
  //  updateRebuild = true;
    SDL_FPoint delta{
        strike.moveDir.x * strike.moveSpeed * dt,
        strike.moveDir.y * strike.moveSpeed * dt
    };
    logManager::logThis("initial");
    logManager::logThis(strike.start.x, strike.start.y);
    logManager::logThis(strike.end.x, strike.end.y);

    strike.start.x += delta.x;
    strike.start.y += delta.y;

    strike.end.x += delta.x;
    strike.end.y += delta.y;
    logManager::logThis("updatedStart");
    logManager::logThis(strike.start.x, strike.start.y);
    logManager::logThis(strike.end.x, strike.end.y);
    // Optional: stop when passing target
    SDL_FPoint toTarget{
        strike.targetPoint.x - strike.start.x,
        strike.targetPoint.y - strike.start.y
    };

    float dot = toTarget.x * strike.moveDir.x + toTarget.y * strike.moveDir.y;

    if (dot <= 0.0f) {
        strike.movementMode = lightningMovementEnum::NONE;
    }
}


void updateStrike(lightningStrike& s, float dt) {
    s.age += dt;

    if (!s.persistent && s.age >= s.lifetime) {
        s.dead = true;
        return;
    }

    // intensity curve
    float t = s.age / s.lifetime;
    s.intensity = (t < 0.2f)
        ? (t / 0.2f)
        : (1.0f - (t - 0.2f) / 0.8f);

    // node jitter
    for (auto& n : s.nodes) {
        float time = s.age * 60.0f;
        n.offset.x = std::sin(time + n.jitterPhase) * n.jitterAmplitude;
        n.offset.y = std::cos(time * 0.9f + n.jitterPhase) * n.jitterAmplitude;
    }
}

void updateStrikes(std::vector<lightningStrike>& strikes, float dt, std::mt19937 rng) {
    // ---- 2. Update strikes ----
    bool needsRebuild = false;
    for (auto& strike : strikes) {
        //rotation
        if (strike.rotateAroundEnd) {
            rotateAroundPoint(dt, strike);
        }
        updateStrike(strike, dt);
        updateMoveTowardTarget(strike, dt, needsRebuild);
        //movement
        if (strike.walkVelocity.x != 0.0f || strike.walkVelocity.y != 0.0f) {
            strike.start.x += strike.walkVelocity.x * dt;
            strike.start.y += strike.walkVelocity.y * dt;
            strike.end.x += strike.walkVelocity.x * dt;
            strike.end.y += strike.walkVelocity.y * dt;

            strike.walkRebuildTimer += dt;
        }
         
        if (strike.walkRebuildInterval > 0.0f &&
            strike.walkRebuildTimer >= strike.walkRebuildInterval) {

            strike.walkRebuildTimer = 0.0f;
            needsRebuild = true;
        }

        strike.rebuildTimer += dt;
        if (strike.rebuildTimer >= strike.rebuildInterval) {
            strike.rebuildTimer = 0.0f;
            needsRebuild = true;

        }

        if (needsRebuild) {
            lightningGenerator::rebuild(strike.start, strike.end, strike.nodes, strike.segments, strike.genCfg, rng);
        }
    }
}

void curateStorms(std::vector<lightningStrike>& strikes, std::vector<lightningStorm>& storms) {
    // ---- 3. Cull dead strikes ----
    strikes.erase(
        std::remove_if(strikes.begin(), strikes.end(),
            [](const lightningStrike& s) { return s.dead; }),
        strikes.end()
    );

    // ---- 4. Cull finished storms ----
    storms.erase(
        std::remove_if(storms.begin(), storms.end(),
            [](const lightningStorm& s) { return s.finished; }),
        storms.end()
    );
}

