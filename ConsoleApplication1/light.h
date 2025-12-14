#pragma once
#include <SDL3/SDL.h>
#include "position.h"

#include <cmath>

struct light {
    position pos; 
    float baseRadius = 200.0f;
    float baseIntensity = 1.0f; 
    float radius = 200.0f;
    float intensity = 1.0f; 
    SDL_Color color = { 255, 255, 255, 255 };

    // Independent pulse toggles
    bool radiusPulse = false;
    bool intensityPulse = false;

    // Radius pulse parameters
    float radiusPulseRange = 0.0f;   // +/- units
    float radiusPulseSpeed = 1.0f;   // radians/sec
    float radiusPulseTime = 0.0f;

    // Intensity pulse parameters
    float intensityPulseRange = 0.0f; // +/- units
    float intensityPulseSpeed = 1.0f; // radians/sec
    float intensityPulseTime = 0.0f;

    light(position p, float r, float i, SDL_Color c): pos(p), baseRadius(r), baseIntensity(i), radius(r), intensity(i), color(c){}

    // Call once per frame
    void update(float deltaTime) {

        // Radius pulsing
        if (radiusPulse) {
            radiusPulseTime += deltaTime;
            float s = std::sinf(radiusPulseTime * radiusPulseSpeed);
            radius = baseRadius + s * radiusPulseRange;
        }
        else {
            radius = baseRadius;
        }

        // Intensity pulsing
        if (intensityPulse) {
            intensityPulseTime += deltaTime;
            float s = std::sinf(intensityPulseTime * intensityPulseSpeed);
            intensity = baseIntensity + s * intensityPulseRange;
            if (intensity < 0.0f) intensity = 0.0f;
        }
        else {
            intensity = baseIntensity;
        }
    }

    // Radius pulse control
    void enableRadiusPulse(float range, float speed) {
        radiusPulse = true;
        radiusPulseRange = range;
        radiusPulseSpeed = speed;
    }

    void disableRadiusPulse() {
        radiusPulse = false;
        radiusPulseTime = 0.0f;
        radius = baseRadius;
    }

    // Intensity pulse control
    void enableIntensityPulse(float range, float speed) {
        intensityPulse = true;
        intensityPulseRange = range;
        intensityPulseSpeed = speed;
    }

    void disableIntensityPulse() {
        intensityPulse = false;
        intensityPulseTime = 0.0f;
        intensity = baseIntensity;
    }
};
