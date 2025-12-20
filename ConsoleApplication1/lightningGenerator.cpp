#pragma once
#include "lightningGenerator.h"
#include <vector>
#include <random>
#include <cmath>



static void subdivide(std::vector<SDL_FPoint>& points, SDL_FPoint a, SDL_FPoint b, float displacement, int depth, std::mt19937& rng) {
    if (depth == 0) {
        points.push_back(b);
        return;
    }

    std::uniform_real_distribution<float> dist(-displacement, displacement);

    SDL_FPoint mid{
        (a.x + b.x) * 0.5f,
        (a.y + b.y) * 0.5f
    };

    SDL_FPoint dir{ b.x - a.x, b.y - a.y };
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 0.0001f) {
        dir.x /= len;
        dir.y /= len;
    }

    SDL_FPoint perp{ -dir.y, dir.x };
    mid.x += perp.x * dist(rng);
    mid.y += perp.y * dist(rng);

    subdivide(points, a, mid, displacement * 0.5f, depth - 1, rng);
    subdivide(points, mid, b, displacement * 0.5f, depth - 1, rng);
}


lightningStrike lightningGenerator::generate(SDL_FPoint start, SDL_FPoint end, const lightningGeneratorConfig& cfg, uint32_t seed) {
    lightningStrike strike;
    strike.seed = seed;

    std::mt19937 rng(seed);

    std::vector<SDL_FPoint> points;
    points.push_back(start);

    subdivide(points, start, end, cfg.displacement, cfg.recursionDepth, rng);

    // Convert points to nodes
    for (auto& p : points) {
        lightningNode node;
        node.basePos = p;
        node.offset = { 0, 0 };
        node.jitterPhase = std::uniform_real_distribution<float>(0, 6.28f)(rng);
        node.jitterAmplitude = cfg.jitterAmplitude;
        node.colorPhase = std::uniform_real_distribution<float>(0, 6.28f)(rng);

        strike.nodes.push_back(node);
    }

    // Build segments
    for (size_t i = 0; i + 1 < strike.nodes.size(); ++i) {
        lightningSegment seg;
        seg.a = (uint16_t)i;
        seg.b = (uint16_t)(i + 1);

        float t = (float)i / (strike.nodes.size() - 1);
        seg.baseWidth = cfg.baseWidth * (1.0f - t);

        strike.segments.push_back(seg);
    }

    return strike;
}

