#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_Fpoint_json.h"
#include "SDL_Color_Json.h"

using json = nlohmann::ordered_json;


struct drop {
    SDL_FPoint start;
    SDL_FPoint end;

    SDL_FPoint velocity;
    SDL_Color color;

    void update(float dt);
};

inline void to_json(json& j, const drop& d ) {
	j = json::object();
	j["start"] = d.start;
    j["end"] = d.end;
    j["velocity"] = d.velocity;
    j["color"] = d.color;
}

inline void from_json(const json& j, drop& d) {

	j.at("start").get_to(d.start);
    j.at("end").get_to(d.end);
    j.at("velocity").get_to(d.velocity);
    j.at("color").get_to(d.color);
}