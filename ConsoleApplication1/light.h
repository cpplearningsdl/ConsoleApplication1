#pragma once
#include <SDL3/SDL.h>
#include "position.h"
#include "lightModulationEnum.h"
#include "json.hpp"
#include <cmath>

using json = nlohmann::ordered_json;


struct light {
    position pos;

    // Base values
    float baseRadius = 200.0f;
    float baseIntensity = 1.0f;

    // Runtime values
    float radius = 200.0f;
    float intensity = 1.0f;

    SDL_Color color = { 255, 255, 255, 255 };

    // Radius modulation
    lightModulation radiusMode = lightModulation::None;
    float radiusRange = 0.0f;
    float radiusSpeed = 1.0f;
    float radiusTime = 0.0f;

    // Intensity modulation
    lightModulation intensityMode = lightModulation::None;
    float intensityRange = 0.0f;
    float intensitySpeed = 1.0f;
    float intensityTime = 0.0f;

    light(position p, float r, float i, SDL_Color c)
        : pos(p),
        baseRadius(r),
        baseIntensity(i),
        radius(r),
        intensity(i),
        color(c)
    {
    }

    void update(float dt) { 

        // Radius
        switch (radiusMode) {
        case lightModulation::Pulse:
            radiusTime += dt;
            radius = baseRadius + sinf(radiusTime * radiusSpeed) * radiusRange;
            break;

        case lightModulation::Oscillation:
            radiusTime += dt;
            radius = baseRadius
                + (0.5f * (1.0f - cosf(radiusTime * radiusSpeed))) * radiusRange;
            break;

        default:
            radius = baseRadius;
            break;
        }

        // Intensity
        switch (intensityMode) {
        case lightModulation::Pulse:
            intensityTime += dt;
            intensity = baseIntensity
                + sinf(intensityTime * intensitySpeed) * intensityRange;
            break;

        case lightModulation::Oscillation:
            intensityTime += dt;
            intensity = baseIntensity
                + (0.5f * (1.0f - cosf(intensityTime * intensitySpeed)))
                * intensityRange;
            break;

        default:
            intensity = baseIntensity;
            break;
        }

        if (intensity < 0.0f)
            intensity = 0.0f;
    }


    void setRadiusPulse(float range, float speed) {
        radiusMode = lightModulation::Pulse;
        radiusRange = range;
        radiusSpeed = speed;
    }

    void setRadiusOscillation(float range, float speed) {
        radiusMode = lightModulation::Oscillation;
        radiusRange = range;
        radiusSpeed = speed;
    }

    void disableRadiusModulation() {
        radiusMode = lightModulation::None;
        radiusTime = 0.0f;
        radius = baseRadius;
    }
     

    void setIntensityPulse(float range, float speed) {
        intensityMode = lightModulation::Pulse;
        intensityRange = range;
        intensitySpeed = speed;
    }

    void setIntensityOscillation(float range, float speed) {
        intensityMode = lightModulation::Oscillation;
        intensityRange = range;
        intensitySpeed = speed;
    }

    void disableIntensityModulation() {
        intensityMode = lightModulation::None;
        intensityTime = 0.0f;
        intensity = baseIntensity;
    }
};



//LIGHT
inline void to_json(json& j, const light& l) {
    j = json{
        {"pos", l.pos},

        {"baseRadius", l.baseRadius},
        {"baseIntensity", l.baseIntensity},

        {"radius", l.radius},
        {"intensity", l.intensity},

        {"color", json{
            {"r", l.color.r},
            {"g", l.color.g},
            {"b", l.color.b},
            {"a", l.color.a}
        }},

        {"radiusMode", l.radiusMode},
        {"radiusRange", l.radiusRange},
        {"radiusSpeed", l.radiusSpeed},
        {"radiusTime", l.radiusTime},

        {"intensityMode", l.intensityMode},
        {"intensityRange", l.intensityRange},
        {"intensitySpeed", l.intensitySpeed},
        {"intensityTime", l.intensityTime}
    };
}

inline void from_json(const json& j, light& l) {
    if (j.contains("pos") && j["pos"].is_object())
        j.at("pos").get_to(l.pos);

    l.baseRadius = j.value("baseRadius", 200.0f);
    l.baseIntensity = j.value("baseIntensity", 1.0f);

    l.radius = j.value("radius", l.baseRadius);
    l.intensity = j.value("intensity", l.baseIntensity);

    if (j.contains("color") && j["color"].is_object()) {
        l.color.r = j["color"].value("r", 255);
        l.color.g = j["color"].value("g", 255);
        l.color.b = j["color"].value("b", 255);
        l.color.a = j["color"].value("a", 255);
    }

    if (j.contains("radiusMode"))
        j.at("radiusMode").get_to(l.radiusMode);

    l.radiusRange = j.value("radiusRange", 0.0f);
    l.radiusSpeed = j.value("radiusSpeed", 1.0f);
    l.radiusTime = j.value("radiusTime", 0.0f);

    if (j.contains("intensityMode"))
        j.at("intensityMode").get_to(l.intensityMode);

    l.intensityRange = j.value("intensityRange", 0.0f);
    l.intensitySpeed = j.value("intensitySpeed", 1.0f);
    l.intensityTime = j.value("intensityTime", 0.0f);
}