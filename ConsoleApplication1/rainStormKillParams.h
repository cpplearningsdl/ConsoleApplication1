#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "rainKillTypeEnum.h"
#include "SDL_FrectHelpers.h"
#include "SDL_Fpoint_json.h"

struct rainKillParams {
    rainKillType type = rainKillType::LOWER_Y;

    // LOWER_Y
    float lowerY = 0.0f;

    // RECTANGLE
    SDL_FRect rect{};

    // CIRCLE
    SDL_FPoint center{};
    float radius = 0.0f;

    // ELLIPSE
    float radiusX = 0.0f;
    float radiusY = 0.0f;
};

inline void to_json(json& j, const rainKillParams& s) {
    j = json::object();

    j["type"] = s.type;
    j["lowerY"] = s.lowerY;
    j["rect"] = s.rect;
    j["center"] = s.center;
    j["radius"] = s.radius;
    j["radiusX"] = s.radiusX;
    j["radiusY"] = s.radiusY;
}

inline void from_json(const json& j, rainKillParams& s) {
    j.at("type").get_to(s.type);
    j.at("lowerY").get_to(s.lowerY);
    j.at("rect").get_to(s.rect);
    j.at("center").get_to(s.center);
    j.at("radius").get_to(s.radius);
    j.at("radiusX").get_to(s.radiusX);
    j.at("radiusY").get_to(s.radiusY);
}