#pragma once
#include <SDL3/SDL.h>


static SDL_Color lerpColor(const SDL_Color& a, const SDL_Color& b, float t) {
    return {
        Uint8(a.r + (b.r - a.r) * t),
        Uint8(a.g + (b.g - a.g) * t),
        Uint8(a.b + (b.b - a.b) * t),
        Uint8(a.a + (b.a - a.a) * t)
    };
}
