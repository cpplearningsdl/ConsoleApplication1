#pragma once
#include <random>
#include <cmath>
#include <algorithm> 
#include <SDL3/SDL.h>
#include "lightningManager.h"
#include "lightningManagerHelperFunctions.h"
#include "lightningGenerator.h"
#include "lightningStormDef.h"
#include "windowSettings.h"

lightningManager::lightningManager() {

}
lightningManager::~lightningManager() {
    storms.clear();
    strikes.clear();
}


void lightningManager::addStorm(const lightningStormDef& def, SDL_FPoint start, SDL_FPoint end) {
    lightningStorm storm;
    storm.def = &def;
    storm.start = start;
    storm.end = end;
    storm.spawnTimer = 0.0f;

    storms.push_back(storm);
}
void lightningManager::addStorm(std::string id, SDL_FPoint start, SDL_FPoint end) {
    lightningStorm storm;
    storm.def = defaultStorms.get(id);
    storm.start = start;
    storm.end = end;
    storm.spawnTimer = 0.0f;

    storms.push_back(storm);
}

void lightningManager::update(float dt) {
    // ---- 1. Update storms + spawn strikes ----
    for (auto& storm : storms) {
        storm.age += dt;
        storm.spawnTimer -= dt;

        if (!storm.finished && storm.spawnTimer <= 0.0f && storm.strikesSpawned < storm.def->config.maxStrikes) {
            storm.spawnTimer = storm.def->config.strikeInterval;

            spawnStrikeFromStorm(storm);
            storm.strikesSpawned++;
        }

        if (storm.age >= storm.def->config.stormDuration) {
            storm.finished = true;
        }
    }

    // ---- 2. Update strikes ----
    for (auto& strike : strikes) {
        if (strike.rotateAroundEnd) {
            rotateAroundPoint(dt, strike);
        }
        updateStrike(strike, dt);

        strike.rebuildTimer += dt;
        if (strike.rebuildTimer >= strike.rebuildInterval) {
            strike.rebuildTimer = 0.0f;

            lightningGenerator::rebuild(strike.start, strike.end, strike.nodes, strike.segments, strike.genCfg, rng);
        }
    }

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
void lightningManager::updateStrike(lightningStrike& s, float dt) {
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

void lightningManager::spawnStrikeFromStorm(lightningStorm& storm) {
    const auto& cfg = storm.def->config;

    std::mt19937 rng(SDL_GetTicks());

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
        end = randomVerticalBottom(start, logicalW, logicalH, 200.0f,cfg.maxHorizontalDelta, rng);
        break; 
    case lightningPlacementMode::RADIUSFROMPOINT:
        start = randomPointInRadius(storm.start, cfg.radius, rng);
        end = randomPointInRadius(storm.start, cfg.radius, rng);
        break;

    case lightningPlacementMode::FIXEDENDPOINTS:
    default:
        break;
    }

    lightningStrike strike =
        lightningGenerator::generate(
            start, end, cfg.generator, rng()
        );

    strike.start = start;
    strike.end = end;
    strike.lifetime = cfg.strikeLifetime;
    strike.persistent = cfg.persistentStrike;

    strike.rotateAroundEnd = cfg.rotateStrikeStart;
    strike.rotationSpeed = cfg.rotationSpeed;
    strike.rotationRadius = cfg.rotationRadius;
    strike.rebuildInterval = cfg.rebuildInterval;

    strikes.push_back(std::move(strike));
}



void lightningManager::render(SDL_Renderer* r) {
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_ADD);  
    for (const auto& s : strikes) {
        for (const auto& seg : s.segments) {
            const auto& a = s.nodes[seg.a];
            const auto& b = s.nodes[seg.b];

            SDL_Color c{
                Uint8(220 * s.intensity),
                Uint8(235 * s.intensity),
                Uint8(255 * s.intensity),
                Uint8(255)
            };

            SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);

            SDL_RenderLine(
                r,
                a.basePos.x + a.offset.x,
                a.basePos.y + a.offset.y,
                b.basePos.x + b.offset.x,
                b.basePos.y + b.offset.y
            );
        }
    }
}

 