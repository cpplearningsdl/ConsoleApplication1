#pragma once
#include <vector>
#include <SDL3/SDL.h> 
#include "json.hpp"
#include "SDL_fpoint_Json.h"
#include "SDL_Color_json.h"
#include "fireColorProfile.h"
#include "fireLine.h"
#include "emberParticle.h"


struct fire {
    SDL_FPoint origin;
    float size;

    SDL_FPoint baseLeft;
    SDL_FPoint baseRight;

    fireColorProfile colors;

    std::vector<fireLine> primary;
    std::vector<fireLine> secondary;
    std::vector<emberParticle> embers;
    void update(float dt);
};

inline void to_json(json& j, const fire& p) {
    j = json::object();

    j["origin"] = p.origin;
    j["size"] = p.size;
    j["baseLeft"] = p.baseLeft;
    j["baseRight"] = p.baseRight;
    j["colors"] = p.colors;

    j["primary"] = p.primary;
    j["secondary"] = p.secondary;
    j["embers"] = p.embers;
}

inline void from_json(const json& j, fire& p) {
    j.at("origin").get_to(p.origin);
    j.at("size").get_to(p.size);
    j.at("baseLeft").get_to(p.baseLeft);
    j.at("baseRight").get_to(p.baseRight);
    j.at("colors").get_to(p.colors);

    // vectors — default to empty if missing
    p.primary = j.value("primary", std::vector<fireLine>{});
    p.secondary = j.value("secondary", std::vector<fireLine>{});
    p.embers = j.value("embers", std::vector<emberParticle>{});
}