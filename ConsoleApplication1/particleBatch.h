#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_Fpoint_json.h"
#include "SDL_Color_Helpers.h"

struct particleBatch {
	std::vector<SDL_FPoint> points;
	std::vector<SDL_Color> colors; 

    void clear()
    {
        points.clear();
        colors.clear();
    }

    void reserve(size_t count)
    {
        points.reserve(count);
        colors.reserve(count);
    }
};

// Sort the batch by color, keeping points and colors aligned
inline void sortParticleBatchByColorInPlace(particleBatch& batch) {
    size_t n = batch.points.size();
    if (n == 0) return;

    // Step 1: Build index array
    std::vector<size_t> order(n);
    std::iota(order.begin(), order.end(), 0);

    // Step 2: Sort indices by color
    std::sort(order.begin(), order.end(),
        [&](size_t a, size_t b) {
            return std::memcmp(&batch.colors[a], &batch.colors[b], sizeof(SDL_Color)) < 0;
        });

    // Step 3: In-place reorder points and colors
    std::vector<bool> visited(n, false);

    for (size_t i = 0; i < n; ++i)
    {
        if (visited[i] || order[i] == i)
            continue;

        size_t j = i;
        SDL_FPoint tmpPos = batch.points[i];
        SDL_Color tmpCol = batch.colors[i];

        while (true)
        {
            size_t next = order[j];
            if (next == i) break;

            batch.points[j] = batch.points[next];
            batch.colors[j] = batch.colors[next];
            visited[j] = true;
            j = next;
        }

        batch.points[j] = tmpPos;
        batch.colors[j] = tmpCol;
        visited[j] = true;
    }
}


inline void sortParticleBatchByPackedColor(particleBatch& batch)
{
    size_t n = batch.points.size();
    if (n == 0) return;

    // Pack colors into uint32_t
    std::vector<uint32_t> packedColors(n);
    for (size_t i = 0; i < n; ++i)
        packedColors[i] = packColor(batch.colors[i]);

    // Build index array
    std::vector<size_t> order(n);
    std::iota(order.begin(), order.end(), 0);

    // Sort indices by packed color
    std::sort(order.begin(), order.end(),
        [&](size_t a, size_t b) {
            return packedColors[a] < packedColors[b];
        });

    // In-place permutation using cycle method
    std::vector<char> visited(n, 0);

    for (size_t i = 0; i < n; ++i)
    {
        if (visited[i] || order[i] == i) continue;

        size_t j = i;
        SDL_FPoint tmpPos = batch.points[i];
        SDL_Color tmpCol = batch.colors[i];

        while (true)
        {
            size_t next = order[j];
            if (next == i) break;

            batch.points[j] = batch.points[next];
            batch.colors[j] = batch.colors[next];
            visited[j] = 1;
            j = next;
        }

        batch.points[j] = tmpPos;
        batch.colors[j] = tmpCol;
        visited[j] = 1;
    }
}