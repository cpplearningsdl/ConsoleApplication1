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

static void reduceNodes(std::vector<lightningNode>& nodes, int maxNodes) {
    if ((int)nodes.size() <= maxNodes)
        return;

    std::vector<lightningNode> reduced;
    reduced.reserve(maxNodes);

    for (int i = 0; i < maxNodes; ++i) {
        float t = float(i) / float(maxNodes - 1);
        int idx = int(t * (nodes.size() - 1));
        reduced.push_back(nodes[idx]);
    }

    nodes.swap(reduced);
}
 

lightningStrike lightningGenerator::generate(SDL_FPoint start, SDL_FPoint end, const lightningGeneratorConfig& cfg, uint32_t seed, std::optional<SDL_FPoint> target) {
    lightningStrike strike;
    strike.seed = seed; 
    std::mt19937 rng(seed);
    strike.rng = rng;
    strike.genCfg = cfg;

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
    //"lightning detail"
    if (cfg.maxNodes > 0 && strike.nodes.size() > cfg.maxNodes) {
        reduceNodes(strike.nodes, cfg.maxNodes);
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

void lightningGenerator::rebuild(SDL_FPoint start, SDL_FPoint end, std::vector<lightningNode>& nodes, std::vector<lightningSegment>& segments, const lightningGeneratorConfig& cfg, std::mt19937& rng) {
    // ---- 1. generate polyline ----
    std::vector<SDL_FPoint> points;
    points.reserve(static_cast<std::vector<SDL_FPoint, std::allocator<SDL_FPoint>>::size_type>(1) << cfg.recursionDepth);

    points.push_back(start);
    subdivide(points, start, end, cfg.displacement, cfg.recursionDepth, rng);

    // ---- 2. resize nodes (reuse memory) ----
    nodes.resize(points.size());

    for (size_t i = 0; i < points.size(); ++i) {
        auto& n = nodes[i];

        n.basePos = points[i];
        n.offset = { 0.0f, 0.0f };
        n.jitterAmplitude = cfg.jitterAmplitude;

        // Preserve existing phases if present
        if (n.jitterPhase == 0.0f)
            n.jitterPhase = std::uniform_real_distribution<float>(0.0f, 6.28318f)(rng);

        if (n.colorPhase == 0.0f)
            n.colorPhase = std::uniform_real_distribution<float>(0.0f, 6.28318f)(rng);
    }

    // ---- 3. rebuild segments (simple chain) ----
    segments.clear();
    segments.reserve(nodes.size() > 1 ? nodes.size() - 1 : 0);

    for (int i = 0; i < (int)nodes.size() - 1; ++i) {
        segments.emplace_back(lightningSegment{ static_cast<uint16_t>(i), static_cast<uint16_t>(i + 1), cfg.baseWidth });
    }
}

