#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"

using json = nlohmann::ordered_json;

inline void to_json(json& j, const SDL_Vertex& v) {
    j = json{
        { "position", {
            { "x", v.position.x },
            { "y", v.position.y }
        }},
        { "color", {
            { "r", v.color.r },
            { "g", v.color.g },
            { "b", v.color.b },
            { "a", v.color.a }
        }},
        { "texCoord", {
            { "x", v.tex_coord.x },
            { "y", v.tex_coord.y }
        }}
    };
}

inline void from_json(const json& j, SDL_Vertex& v) {
    const auto& p = j.at("position");
    v.position.x = p.at("x").get<float>();
    v.position.y = p.at("y").get<float>();

    const auto& c = j.at("color");
    v.color.r = c.at("r").get<Uint8>();
    v.color.g = c.at("g").get<Uint8>();
    v.color.b = c.at("b").get<Uint8>();
    v.color.a = c.at("a").get<Uint8>();

    const auto& t = j.at("texCoord");
    v.tex_coord.x = t.at("x").get<float>();
    v.tex_coord.y = t.at("y").get<float>();
}
