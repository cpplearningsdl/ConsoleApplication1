#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_fpoint_Json.h"
#include "SDL_Color_json.h"

using json = nlohmann::ordered_json;

struct fireColorProfile {
    SDL_Color primaryLine;    // main flame
    SDL_Color primaryMin;
    SDL_Color primaryMax;
    SDL_Color secondaryLine;  // hot flicker
    SDL_Color secondaryMin;
    SDL_Color secondaryMax;
    SDL_Color emberMin;       // ember gradient start
    SDL_Color emberMax;       // ember gradient end
};

inline void to_json(json& j, const fireColorProfile& p) {
    j = json::object();

    j["primaryLine"] = p.primaryLine;
    j["primaryMin"] = p.primaryMin;
    j["primaryMax"] = p.primaryMax;

    j["secondaryLine"] = p.secondaryLine;
    j["secondaryMin"] = p.secondaryMin;
    j["secondaryMax"] = p.secondaryMax;

    j["emberMin"] = p.emberMin;
    j["emberMax"] = p.emberMax;
}

inline void from_json(const json& j, fireColorProfile& p) {
    j.at("primaryLine").get_to(p.primaryLine);
    j.at("primaryMin").get_to(p.primaryMin);
    j.at("primaryMax").get_to(p.primaryMax);

    j.at("secondaryLine").get_to(p.secondaryLine);
    j.at("secondaryMin").get_to(p.secondaryMin);
    j.at("secondaryMax").get_to(p.secondaryMax);

    j.at("emberMin").get_to(p.emberMin);
    j.at("emberMax").get_to(p.emberMax);
}