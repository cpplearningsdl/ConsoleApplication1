#pragma once
#include <SDL3/SDL.h>
#include <cmath>
#include "weatherType.h"
#include "logManager.h"

using json = nlohmann::ordered_json;
 
struct ambiance {
    bool enabled = true;

    Uint8 darknessAlpha = 0;
    float normalized = 0.0f;

    SDL_Color tint = { 0, 0, 0, 255 };

    weatherType weather = weatherType::CLEAR;

    // Debug / info
    float timeNormalized = 0.0f; // 0–1 through the day

    void setDarkness(Uint8 a) {
        darknessAlpha = a;
        normalized = a / 255.0f;
    }
};

inline void to_json(json& j, const ambiance& a) {
    j = {
        {"enabled", a.enabled},
        {"darknessAlpha", a.darknessAlpha},
        {"weather", a.weather},
        {"timeNormalized", a.timeNormalized}
    };
}

inline void from_json(const json& j, ambiance& a) {
    j.at("enabled").get_to(a.enabled);
    j.at("darknessAlpha").get_to(a.darknessAlpha);
    j.at("weather").get_to(a.weather);
    j.at("timeNormalized").get_to(a.timeNormalized);
}