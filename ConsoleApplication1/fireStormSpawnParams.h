#include <cmath>
#include <algorithm> 
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_Fpoint_json.h"
#include "fireSpawnTypeEnum.h"

using json = nlohmann::ordered_json;

struct fireStormSpawnParams {
    bool spread = false;
    float spreadInterval = 0.5f;
    float spreadChance = 0.0f;
    int maxFiresFromSpread = 0;

    fireSpawnTypeEnum spawnType = fireSpawnTypeEnum::NONE;

    SDL_FPoint spawnPoint{ 0.0f, 0.0f };

    float spawnRadius = 0.0f;

    SDL_FPoint topLeft{ 0.0f, 0.0f };
    SDL_FPoint bottomRight{ 0.0f, 0.0f };

    int minFires = 1;
    int maxFires = 1;
};

inline void to_json(json& j, const fireStormSpawnParams& fsp) {
    j = json::object();

    j["spread"] = fsp.spread;
    j["spreadInterval"] = fsp.spreadInterval;
    j["spreadChance"] = fsp.spreadChance;
    j["maxFiresFromSpread"] = fsp.maxFiresFromSpread;
    j["spawnType"] = fsp.spawnType;
    j["spawnPoint"] = fsp.spawnPoint;
    j["spawnRadius"] = fsp.spawnRadius;
    j["topLeft"] = fsp.topLeft;
    j["bottomRight"] = fsp.bottomRight;
    j["minFires"] = fsp.minFires;
    j["maxFires"] = fsp.maxFires; 
}

 

inline void from_json(const json& j, fireStormSpawnParams& fsp) { 
    j.at("spread").get_to(fsp.spread);
    j.at("spreadInterval").get_to(fsp.spreadInterval);
    j.at("spreadChance").get_to(fsp.spreadChance);
    j.at("maxFiresFromSpread").get_to(fsp.maxFiresFromSpread);
    j.at("spawnType").get_to(fsp.spawnType);
    j.at("spawnPoint").get_to(fsp.spawnPoint);
    j.at("spawnRadius").get_to(fsp.spawnRadius);
    j.at("topLeft").get_to(fsp.topLeft);
    j.at("bottomRight").get_to(fsp.bottomRight);
    j.at("minFires").get_to(fsp.minFires);
    j.at("maxFires").get_to(fsp.maxFires);
     
    fsp.spawnRadius = std::max(0.0f, fsp.spawnRadius); 
    fsp.minFires = std::max(1, fsp.minFires);
    fsp.maxFires = std::max(fsp.minFires, fsp.maxFires);
    fsp.maxFiresFromSpread = std::max(1, fsp.maxFiresFromSpread);
}