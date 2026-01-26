#pragma once
#include "particleSpawnType.h"
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_fpoint_Json.h"


using json = nlohmann::ordered_json;

struct particleSpawnParams {
    particleSpawnType type = particleSpawnType::POINT;

    SDL_FPoint origin = { -100.0f, -100.0f };

    float radiusInner = 0.0f; 
    float radiusOuter = 0.0f;  
};

inline void to_json(json& j, const particleSpawnParams& pcr) {
    j = json::object();

    j["type"] = pcr.type;
    j["origin"] = pcr.origin;
    j["radiusInner"] = pcr.radiusInner;
    j["radiusOuter"] = pcr.radiusOuter;
}

inline void from_json(const json& j, particleSpawnParams& pcr) {
    j.at("type").get_to(pcr.type);
    j.at("origin").get_to(pcr.origin);
    j.at("radiusInner").get_to(pcr.radiusInner);
    j.at("radiusOuter").get_to(pcr.radiusOuter);
}