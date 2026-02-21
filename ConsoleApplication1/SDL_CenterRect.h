#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_Fpoint_json.h"

using json = nlohmann::ordered_json;

struct centerRect {
    SDL_FPoint center;
    float width;
    float height;

    const SDL_FRect getSDLRect() const;
};

inline const SDL_FRect centerRect::getSDLRect() const {
    SDL_FRect r{};
    r.w = width;
    r.h = height;
    r.x = center.x - width * 0.5f;
    r.y = center.y - height * 0.5f;
    return r;
}

inline void to_json(json& j, const centerRect& s) {
    j = json::object();

    j["center"] = s.center;
    j["width"] = s.width;
    j["height"] = s.height;
}

inline void from_json(const json& j, centerRect& s) {
    j.at("center").get_to(s.center);
    j.at("width").get_to(s.width);
    j.at("height").get_to(s.height);
}