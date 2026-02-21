#pragma once
#include <SDL3/SDL.h>
#include "rainStormSpawnTypeEnum.h"
#include "SDL_CenterRect.h" 
#include "SDL_Fpoint_json.h"

struct rainStormSpawnParams {
    rainSpawnTypeEnum type = rainSpawnTypeEnum::FULLSCREEN_TOPDOWN;
    float emitTime = 0.85f;

    // Used by RECTANGLE
    centerRect rect{};

    // Used by RADIUS / ELLIPSE
    SDL_FPoint center{};
    float radius = 0.0f;        // circle
    float radiusX = 0.0f;       // ellipse
    float radiusY = 0.0f;

    // Vertical bounds
    float spawnY = 0.0f;        // usually top of screen or rect.top
};

inline void to_json(json& j, const rainStormSpawnParams& rsp) {
    j = json::object();

    j["type"] = rsp.type;
    j["emitTime"] = rsp.emitTime;
    j["rect"] = rsp.rect;
    j["center"] = rsp.center;
    j["radius"] = rsp.radius;
    j["radiusX"] = rsp.radiusX;
    j["radiusY"] = rsp.radiusY;
    j["spawnY"] = rsp.spawnY;

}



inline void from_json(const json& j, rainStormSpawnParams& rsp) {
    j.at("type").get_to(rsp.type);
    j.at("emitTime").get_to(rsp.emitTime);
    j.at("rect").get_to(rsp.rect);
    j.at("center").get_to(rsp.center);
    j.at("radius").get_to(rsp.radius);
    j.at("radiusX").get_to(rsp.radiusX);
    j.at("radiusY").get_to(rsp.radiusY);
    j.at("spawnY").get_to(rsp.spawnY);


}