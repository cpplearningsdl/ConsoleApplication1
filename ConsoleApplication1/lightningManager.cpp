#pragma once
#include <random>
#include  <cmath>
#include <SDL3/SDL.h>
#include "lightningManager.h"
#include "lightningGenerator.h"
#include "lightningStormDef.h"
#include "windowSettings.h"

lightningManager::lightningManager() {

}
lightningManager::~lightningManager() {
    storms.clear();
    strikes.clear();
}

static SDL_FPoint randomPointOnScreen(int w, int h, std::mt19937& rng) {
    std::uniform_real_distribution<float> x(0, (float)w);
    std::uniform_real_distribution<float> y(0, (float)h);
    return { x(rng), y(rng) };
}

static SDL_FPoint randomPointInRadius(SDL_FPoint center, float r, std::mt19937& rng) {
    std::uniform_real_distribution<float> angle(0, 6.28318f);
    std::uniform_real_distribution<float> radius(0, r);
    float a = angle(rng);
    float d = radius(rng);
    return {
        center.x + std::cos(a) * d,
        center.y + std::sin(a) * d
    };
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

        if (!storm.finished && storm.spawnTimer <= 0.0f) {
            storm.spawnTimer = storm.def->config.strikeInterval;

            spawnStrikeFromStorm(storm);
        }

        if (storm.age >= storm.def->config.stormDuration) {
            storm.finished = true;
        }
    }

    // ---- 2. Update strikes ----
    for (auto& strike : strikes) {
        updateStrike(strike, dt);
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

 