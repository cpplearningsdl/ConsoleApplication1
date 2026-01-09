#pragma once
#include <random>
#include <cmath>
#include <algorithm> 
#include <SDL3/SDL.h>
#include "lightningManager.h"
#include "lightningManagerHelperFunctions.h"
#include "lightningGenerator.h"
#include "lightningStormDef.h"
#include "stormHelperFunctions.h"
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
void lightningManager::addStorm(std::string id, SDL_FPoint start,SDL_FPoint end, SDL_FPoint target) {
    lightningStorm storm;
    storm.def = defaultStorms.get(id);
    storm.start = start;
    storm.target = target;
    storm.spawnTimer = 0.0f;

    storms.push_back(storm);
}

void lightningManager::update(float dt) {
    updateStormAge(storms, dt);
    tryToSpawnStrikes(storms, strikes, dt);
    updateStrikes(strikes, dt, rng);
    curateStorms(strikes, storms); 
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

 