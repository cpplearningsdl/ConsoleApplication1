#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"

using json = nlohmann::ordered_json;

inline SDL_FRect makeRectFromCenter(const SDL_FPoint& pos, float size){
    float half = size * 0.5f;
    return SDL_FRect{
        pos.x - half,
        pos.y - half,
        size,
        size
    };
}

inline void to_json(json& j, const SDL_FRect& r)
{
    j = json{
        {"x", r.x},
        {"y", r.y},
        {"w", r.w},
        {"h", r.h}
    };
}

// Deserialize json -> SDL_FRect
inline void from_json(const json& j, SDL_FRect& r)
{
    j.at("x").get_to(r.x);
    j.at("y").get_to(r.y);
    j.at("w").get_to(r.w);
    j.at("h").get_to(r.h);
}