#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_Fpoint_json.h"
#include "SDL_Color_Helpers.h"

struct particleBatch
{
    std::vector<SDL_FRect> rects;   // render quads
    std::vector<SDL_Color> colors;  // per-rect color

    void clear()
    {
        rects.clear();
        colors.clear();
    }

    void reserve(size_t count)
    {
        rects.reserve(count);
        colors.reserve(count);
    }
};
 

inline void sortParticleBatchByColorInPlace(particleBatch& batch){
    size_t n = batch.rects.size();
    if (n == 0) return;

    std::vector<uint32_t> packedColors(n);
    for (size_t i = 0; i < n; ++i)
        packedColors[i] = packColor(batch.colors[i]);

    std::vector<size_t> order(n);
    std::iota(order.begin(), order.end(), 0);

    std::sort(order.begin(), order.end(),
        [&](size_t a, size_t b) {
            return packedColors[a] < packedColors[b];
        });

    std::vector<char> visited(n, 0);

    for (size_t i = 0; i < n; ++i)
    {
        if (visited[i] || order[i] == i) continue;

        size_t j = i;
        SDL_FRect tmpRect = batch.rects[i];
        SDL_Color tmpColor = batch.colors[i];

        while (true)
        {
            size_t next = order[j];
            if (next == i) break;

            batch.rects[j] = batch.rects[next];
            batch.colors[j] = batch.colors[next];
            visited[j] = 1;
            j = next;
        }

        batch.rects[j] = tmpRect;
        batch.colors[j] = tmpColor;
        visited[j] = 1;
    }
}