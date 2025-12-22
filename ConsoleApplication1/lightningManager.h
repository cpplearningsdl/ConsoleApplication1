#pragma once
#include <vector> 
#include <string>
#include <SDL3/SDL.h>
#include <random>
#include "lightningStormBank.h"
#include "lightningStorm.h"
#include "lightningStrike.h"


class lightningManager {
public:
    lightningManager();
    ~lightningManager();
    void addStorm(const lightningStormDef& def, SDL_FPoint start, SDL_FPoint end);
    void addStorm(std::string id, SDL_FPoint start, SDL_FPoint end);
    void render(SDL_Renderer* r);
    void update(float dt);
    void spawnStrikeFromStorm(lightningStorm& storm);
    void updateStrike(lightningStrike& s, float dt);
     
    lightningManager& getLightningManager() { return *this; }
    std::vector<lightningStrike>& getStrikes() { return strikes; }

private:
    std::vector<lightningStorm> storms;
    std::vector<lightningStrike> strikes;
    lightningStormBank defaultStorms;
    std::mt19937 rng{ std::random_device{}() };
};
