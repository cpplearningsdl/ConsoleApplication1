#pragma once
#include "SDL3/SDL.h"
#include "json.hpp"

using json = nlohmann::ordered_json;

inline void to_json(json& j, const SDL_Color& c) {
    j = json{
        {"r", c.r},
        {"g", c.g},
        {"b", c.b},
        {"a", c.a}
    };
}

inline void from_json(const json& j, SDL_Color& c) {
    c.r = j.value("r", 0);
    c.g = j.value("g", 0);
    c.b = j.value("b", 0);
    c.a = j.value("a", 255);
}