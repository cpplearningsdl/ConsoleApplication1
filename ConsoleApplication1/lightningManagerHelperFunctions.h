#pragma once
#include <random>
#include <cmath>
#include <algorithm> 
#include <SDL3/SDL.h>
#include "lightningStrike.h"


static SDL_FPoint randomVerticalFromTop(int w, std::mt19937& rng) {
    std::uniform_real_distribution<float> x(0.0f, (float)w);
    return { x(rng), 0.0f };
}

static SDL_FPoint randomVerticalTop(int w, int h, std::mt19937& rng) {
    std::uniform_real_distribution<float> x(0.0f, (float)w);
    std::uniform_real_distribution<float> y(0.0f, (float)h);
    return { x(rng), y(rng) };
}

static SDL_FPoint randomVerticalBottom(const SDL_FPoint& top, int w, int h, float maxHeight, float maxHorizontalDelta, std::mt19937& rng) {
    float height = maxHeight > 0.0f
        ? std::uniform_real_distribution<float>(128.0f, maxHeight)(rng)
        : (float)h;

    std::uniform_real_distribution<float> dx(-maxHorizontalDelta, maxHorizontalDelta);

    float x = std::clamp(top.x + dx(rng), 0.0f, (float)w);
    float y = std::clamp(top.y + height, 0.0f, (float)h);

    return { x, y };
}


static SDL_FPoint randomVerticalBottom(float topX, int w, int h, float maxHorizontalDelta, std::mt19937& rng) {
    std::uniform_real_distribution<float> dx(-maxHorizontalDelta, maxHorizontalDelta);

    float x = topX + dx(rng);

    // clamp to screen
    x = std::clamp(x, 0.0f, (float)w);

    return { x, (float)h };
}

static SDL_FPoint randomPointOnScreen(int w, int h, std::mt19937& rng) {
    std::uniform_real_distribution<float> x(0, (float)w);
    std::uniform_real_distribution<float> y(0, (float)h);
    return { x(rng), y(rng) };
}

static SDL_FPoint randomPointInRadius(SDL_FPoint center, float r, std::mt19937& rng) {
    std::uniform_real_distribution<float> angle(0, 6.28318f);
    std::uniform_real_distribution<float> radius(0, r);
    float a = angle(rng);
    float d = radius(rng);
    return {
        center.x + std::cos(a) * d,
        center.y + std::sin(a) * d
    };
}



static void rotateAroundPoint(float dt, lightningStrike& s) {
    if (s.rotateAroundEnd) {
        s.rotationAngle += s.rotationSpeed * dt;

        s.start = {
            s.end.x + std::cos(s.rotationAngle) * s.rotationRadius,
            s.end.y + std::sin(s.rotationAngle) * s.rotationRadius
        };
    }
}