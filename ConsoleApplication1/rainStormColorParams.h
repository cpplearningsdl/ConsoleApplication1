#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_Color_json.h"

struct rainStormColorParams {
    SDL_Color primary{}; 
    SDL_Color secondary{};
    float secondaryChance = 0.0f;
};
 

inline void to_json(json& j, const rainStormColorParams& p) {
    j = json::object(); 
    j["primary"] = p.primary;
    j["secondary"] = p.secondary;
    j["secondaryChance"] = p.secondaryChance;
}

inline void from_json(const json& j, rainStormColorParams& p) {
    j.at("primary").get_to(p.primary);
    j.at("secondary").get_to(p.secondary);
    j.at("secondaryChance").get_to(p.secondaryChance);
}

