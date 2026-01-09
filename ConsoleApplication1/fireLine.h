#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_fpoint_Json.h"
#include "SDL_Color_json.h"

using json = nlohmann::ordered_json;

struct fireLine {
    SDL_FPoint start;
    SDL_FPoint end;
    SDL_FPoint velocity;
    float baseLength;
    float colorT;
    float colorDir;

    void update(float dt, float size);
};

inline void to_json(json& j, const fireLine& p) {
    j = json::object();

    j["start"] = p.start;
    j["end"] = p.end;
    j["velocity"] = p.velocity;
    j["baseLength"] = p.baseLength;
    j["colorT"] = p.colorT;
    j["colorDir"] = p.colorDir;
 
}

inline void from_json(const json& j, fireLine& p) {
    j.at("start").get_to(p.start);
    j.at("end").get_to(p.end);
    j.at("velocity").get_to(p.velocity);
    j.at("baseLength").get_to(p.baseLength);
    j.at("colorT").get_to(p.colorT);
    j.at("colorDir").get_to(p.colorDir);

}