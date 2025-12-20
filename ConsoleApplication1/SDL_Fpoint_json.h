#pragma once
#include "json.hpp" 
#include <SDL3/SDL.h> 

using json = nlohmann::ordered_json;

inline void to_json(json& j, const SDL_FPoint& p) {
    j = json::object();
    j["x"] = p.x;
    j["y"] = p.y;
}

inline void from_json(const json& j, SDL_FPoint& p) {
    p.x = j.at("x").get<float>();
    p.y = j.at("y").get<float>();
}