#include "fireStorm.h"
#include "randomUtilityFunctions.h"
#include "fireGenerator.h"

void fireStorm::update(float dt) {
    age += dt;

    for (auto& f : fires) {
        f.update(dt, def.config.fireLineParams, def.config.emberParams);
    }
    spread(dt);
}

void fireStorm::spread(float dt) {
    if (!def.config.spawnParams.spread || fires.empty()) { return; }
    int maxFiresPlusMaxFiresFromSpread = def.config.spawnParams.maxFires + def.config.spawnParams.maxFiresFromSpread;
    if (fires.size() > 100 || fires.size() > maxFiresPlusMaxFiresFromSpread) { return; }

    const auto& sp = def.config.spawnParams;

    spreadTimer += dt;

    if (spreadTimer < sp.spreadInterval) { return; }

    spreadTimer = 0.0f;

    if (randomFloat(0.0f, 1.0f) > sp.spreadChance) { return; }

    // --- choose source fire ---
    int srcIndex = randomInt(0, (int)fires.size() - 1);
    SDL_FPoint baseOrigin = fires[srcIndex].origin;

    // --- offset within radius ---
    SDL_FPoint offset = randomOffsetInRadius(sp.spawnRadius);
    SDL_FPoint newOrigin = { baseOrigin.x + offset.x, baseOrigin.y + offset.y };

    // --- create new fire ---
    fire newFire = fireGenerator::generateFire(def.config, newOrigin); 
    fires.push_back(std::move(newFire));

}