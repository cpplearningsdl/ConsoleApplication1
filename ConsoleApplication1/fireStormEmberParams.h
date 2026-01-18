#pragma once
#include "SDL3/SDL.h"
#include "SDL_Fpoint_json.h"
#include "SDL_Color_json.h"
#include "emberMovementEnum.h"

struct fireStormEmberParams {
    bool smoke = false; 
    int embersPerFireMin = 0;
    int embersPerFireMax = 0; 
    float emberInterval = 0.0f;
    float emberLifetime = 0.0f;

    SDL_FPoint velocity = { 0.0f, 0.0f };

    SDL_Color emberColorMin;
    SDL_Color emberColorMax;

    emberMovementEnum emberMovement = emberMovementEnum::RISE; 
};


inline void to_json(json& j, const fireStormEmberParams& c) {
    j = json::object();

    j["smoke"] = c.smoke;
    j["embersPerFireMin"] = c.embersPerFireMin;
    j["embersPerFireMax"] = c.embersPerFireMax;
    j["emberInterval"] = c.emberInterval;
    j["emberLifetime"] = c.emberLifetime;
    j["velocity"] = c.velocity;
    j["emberColorMin"] = c.emberColorMin;
    j["emberColorMax"] = c.emberColorMax;
    j["emberMovement"] = c.emberMovement;

}

inline void from_json(const json& j, fireStormEmberParams& c) {
     
    if (j.contains("smoke"))
        c.smoke = j.at("smoke").get<bool>(); 
 
    if (j.contains("embersPerFireMin"))
        c.embersPerFireMin = j.at("embersPerFireMin").get<int>();

    if (j.contains("embersPerFireMax"))
        c.embersPerFireMax = j.at("embersPerFireMax").get<int>();

    if (j.contains("emberInterval"))
        c.emberInterval = j.at("emberInterval").get<float>();

    if (j.contains("emberLifetime"))
        c.emberLifetime = j.at("emberLifetime").get<float>();

    if (j.contains("velocity"))
        c.velocity = j.at("velocity").get<SDL_FPoint>();

    if (j.contains("emberColorMin"))
        c.emberColorMin = j.at("emberColorMin").get<SDL_Color>();

    if (j.contains("emberColorMax"))
        c.emberColorMax = j.at("emberColorMax").get<SDL_Color>();

    if (j.contains("emberMovement"))
        c.emberMovement = j.at("emberMovement").get<emberMovementEnum>();

}