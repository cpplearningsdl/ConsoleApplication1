#pragma once
#include "SDL3/SDL.h"
#include "SDL_Color_Range.h"
#include "json.hpp"

using json = nlohmann::ordered_json;

struct particleConfig {
    float lifetimeMin = 0.5f;
    float lifetimeMax = 1.5f;

    float speedMin = 30.0f;
    float speedMax = 120.0f;

    particleColorRange primaryColor;
    particleColorRange secondaryColor; 
    float secondaryColorChance = 0.25f;
    float colorPhase = 0.0f; 
    float colorSpeed = 1.0f;

    float sizeMin = 1.0f;
    float sizeMax = 3.0f;
};

inline void to_json(json& j, const particleConfig& c) {
    j = json::object();

    j["lifetimeMin"] = c.lifetimeMin;
    j["lifetimeMax"] = c.lifetimeMax;
    j["speedMin"] = c.speedMin;
    j["speedMax"] = c.speedMax;
    j["primaryColor"] = c.primaryColor;
    j["secondaryColor"] = c.secondaryColor;
    j["secondaryColorChance"] = c.secondaryColorChance;
    j["colorPhase"] = c.colorPhase;
    j["colorSpeed"] = c.colorSpeed;
    j["sizeMin"] = c.sizeMin;
    j["sizeMax"] = c.sizeMax;
}

inline void from_json(const json& j, particleConfig& c) {
    c = particleConfig{};

    if (j.contains("lifetimeMin"))
        c.lifetimeMin = j.at("lifetimeMin").get<float>();

    if (j.contains("lifetimeMax"))
        c.lifetimeMax = j.at("lifetimeMax").get<float>();

    if (j.contains("speedMin"))
        c.speedMin = j.at("speedMin").get<float>();

    if (j.contains("speedMax"))
        c.speedMax = j.at("speedMax").get<float>();


    if (j.contains("primaryColor"))
        c.primaryColor = j.at("primaryColor").get<particleColorRange>();

    if (j.contains("secondaryColor"))
        c.secondaryColor = j.at("secondaryColor").get<particleColorRange>();

    if (j.contains("secondaryColorChance"))
        c.secondaryColorChance = j.at("secondaryColorChance").get<float>();

    if (j.contains("colorPhase"))
        c.colorPhase = j.at("colorPhase").get<float>();

    if (j.contains("colorSpeed"))
        c.colorSpeed = j.at("colorSpeed").get<float>();

    if (j.contains("sizeMin"))
        c.sizeMin = j.at("sizeMin").get<float>();

    if (j.contains("sizeMax"))
        c.sizeMax = j.at("sizeMax").get<float>();
}