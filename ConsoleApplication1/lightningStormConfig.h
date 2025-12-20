#pragma once
#include "lightningGeneratorConfig.h"
#include "lightningPlacementModeEnum.h" 
#include "SDL_fpoint_Json.h"
#include "json.hpp"

using json = nlohmann::ordered_json;

struct lightningStormConfig {
    // Strike count / timing
    int minStrikes = 1;
    int maxStrikes = 3;
    float strikeInterval = 0.15f;
    float stormDuration = 2.0f;

    // Placement
    lightningPlacementMode placement = lightningPlacementMode::FIXEDENDPOINTS;

    float radius = 200.0f;                 // for RadiusFromPoint
    SDL_FPoint walkVelocity{ 0, 0 };       // for WalkingEndpoints
    float walkRebuildInterval = 0.05f;     // how often geometry is regenerated

    // Strike behavior
    float strikeLifetime = 0.2f;
    bool persistentStrike = false;         // long-lived lightning

    lightningGeneratorConfig generator;
};
inline void to_json(json& j, const lightningStormConfig& c) {
    j = json::object();

    j["minStrikes"] = c.minStrikes;
    j["maxStrikes"] = c.maxStrikes;
    j["strikeInterval"] = c.strikeInterval;
    j["stormDuration"] = c.stormDuration;
    j["placement"] = c.placement;
    j["radius"] = c.radius;
    j["walkVelocity"] = c.walkVelocity;
    j["walkRebuildInterval"] = c.walkRebuildInterval;
    j["persistentStrike"] = c.persistentStrike;
    j["strikeLifetime"] = c.strikeLifetime;
    j["generator"] = c.generator;
}



inline void from_json(const json& j, lightningStormConfig& c) {
    if (j.contains("minStrikes"))
        c.minStrikes = j.at("minStrikes").get<int>();

    if (j.contains("maxStrikes"))
        c.maxStrikes = j.at("maxStrikes").get<int>();

    if (j.contains("strikeInterval"))
        c.strikeInterval = j.at("strikeInterval").get<float>();

    if (j.contains("stormDuration"))
        c.stormDuration = j.at("stormDuration").get<float>();

    if (j.contains("placement"))
        c.placement = j.at("placement").get<lightningPlacementMode>();

    if (j.contains("radius"))
        c.radius = j.at("radius").get<float>();

    if (j.contains("walkVelocity"))
        c.walkVelocity = j.at("walkVelocity").get<SDL_FPoint>();

    if (j.contains("walkRebuildInterval"))
        c.walkRebuildInterval = j.at("walkRebuildInterval").get<float>();

    if (j.contains("persistentStrike"))
        c.persistentStrike = j.at("persistentStrike").get<bool>();

    if (j.contains("strikeLifetime"))
        c.strikeLifetime = j.at("strikeLifetime").get<float>();

    if (j.contains("generator"))
        c.generator = j.at("generator").get<lightningGeneratorConfig>();

    // ---- sanity clamps ----
    c.minStrikes = std::max(1, c.minStrikes);
    c.maxStrikes = std::max(c.minStrikes, c.maxStrikes);

    c.strikeInterval = std::max(0.01f, c.strikeInterval);
    c.stormDuration = std::max(0.0f, c.stormDuration);

    c.radius = std::max(0.0f, c.radius);
    c.walkRebuildInterval = std::max(0.01f, c.walkRebuildInterval);

    c.strikeLifetime = std::max(0.01f, c.strikeLifetime);
}
