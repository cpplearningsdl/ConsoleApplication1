#pragma once
#include <SDL3/SDL.h>


inline Uint32 packColor(const SDL_Color& c)
{
    return (static_cast<Uint32>(c.a) << 24) |
        (static_cast<Uint32>(c.r) << 16) |
        (static_cast<Uint32>(c.g) << 8) |
        (static_cast<Uint32>(c.b));
}

inline SDL_Color unpackColor(Uint32 packed)
{
    SDL_Color c;
    c.a = static_cast<Uint8>((packed >> 24) & 0xFF);
    c.r = static_cast<Uint8>((packed >> 16) & 0xFF);
    c.g = static_cast<Uint8>((packed >> 8) & 0xFF);
    c.b = static_cast<Uint8>(packed & 0xFF);
    return c;
}
