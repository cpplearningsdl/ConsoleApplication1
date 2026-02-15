#pragma once
#include <SDL3/SDL.h>
#include "rainStormSpawnTypeEnum.h"
#include "SDL_FrectHelpers.h"
#include "SDL_Fpoint_json.h"

struct rainStormSpawnParams {
    rainSpawnTypeEnum type = rainSpawnTypeEnum::FULLSCREEN_TOPDOWN;

    // Used by RECTANGLE
    SDL_FRect rect{};

    // Used by RADIUS / ELLIPSE
    SDL_FPoint center{};
    float radius = 0.0f;        // circle
    float radiusX = 0.0f;       // ellipse
    float radiusY = 0.0f;

    // Vertical bounds
    float spawnY = 0.0f;        // usually top of screen or rect.top
    float lowerY = 0.0f;        // calculated once per storm


    float dropsPerSecond = 300.0f;
    float dropLength = 0.0f;//not implemented, this should be changed to emitLength and used for  the amount of time to emit drops, so storm doesnt end with drops not getting to animate to off screen
};
inline void to_json(json& j, const rainStormSpawnParams& rsp) {
    j = json::object();

    j["type"] = rsp.type;
    j["rect"] = rsp.rect;
    j["center"] = rsp.center;
    j["radius"] = rsp.radius;
    j["radiusX"] = rsp.radiusX;
    j["radiusY"] = rsp.radiusY;
    j["spawnY"] = rsp.spawnY;
    j["lowerY"] = rsp.lowerY;
    j["dropsPerSecond"] = rsp.dropsPerSecond; 
    j["dropLength"] = rsp.dropLength;
}



inline void from_json(const json& j, rainStormSpawnParams& rsp) {
    j.at("type").get_to(rsp.type);
    j.at("rect").get_to(rsp.rect);
    j.at("center").get_to(rsp.center);
    j.at("radius").get_to(rsp.radius);
    j.at("radiusX").get_to(rsp.radiusX);
    j.at("radiusY").get_to(rsp.radiusY);
    j.at("spawnY").get_to(rsp.spawnY);
    j.at("lowerY").get_to(rsp.lowerY);
    j.at("dropsPerSecond").get_to(rsp.dropsPerSecond); 
    j.at("dropLength").get_to(rsp.dropLength);
    rsp.dropsPerSecond = std::max(1.0f, 100.0f);
    rsp.dropLength = std::max(0.1f, rsp.dropLength * 3);
}