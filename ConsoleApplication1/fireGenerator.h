#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "fireStorm.h"
#include "fireStormDef.h"
#include "fireStormEmberParams.h"

class fireGenerator {
public: 
    static void generateStorm(fireStorm& s, int fireCount);
    static fire generateFire(const fireStormConfig& cfg, const SDL_FPoint& origin);
    static emberParticle generateEmber(const fireStormEmberParams& emberCfg, const SDL_FPoint& origin);
private:
    static SDL_FPoint generateOrigin(const fireStormSpawnParams& spawn);  
    static std::vector<fireLine> generateFireLines(const SDL_FPoint& origin, int count, const fireLineParams& cfg, float halfWidth, float size);

};
