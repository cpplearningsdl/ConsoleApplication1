#pragma once
#include <random>
#include <cmath>
#include "SDL3/SDL.h"
#include "SDL_Color_Json.h"
#include "randomUtilityFunctions.h"
#include "json.hpp"

using json = nlohmann::ordered_json;

struct particleColorRange {
    SDL_Color start;
    SDL_Color end;
};

inline SDL_Color randomColorInRange(const particleColorRange& range){
    SDL_Color c = {};

    int rMin = std::min(range.start.r, range.end.r);
    int rMax = std::max(range.start.r, range.end.r);

    int gMin = std::min(range.start.g, range.end.g);
    int gMax = std::max(range.start.g, range.end.g);

    int bMin = std::min(range.start.b, range.end.b);
    int bMax = std::max(range.start.b, range.end.b);

    int aMin = std::min(range.start.a, range.end.a);
    int aMax = std::max(range.start.a, range.end.a);

    std::uniform_int_distribution<int> r(rMin, rMax);
    std::uniform_int_distribution<int> g(gMin, gMax);
    std::uniform_int_distribution<int> b(bMin, bMax);
    std::uniform_int_distribution<int> a(aMin, aMax);

    c.r = static_cast<Uint8>(r(gRng));
    c.g = static_cast<Uint8>(g(gRng));
    c.b = static_cast<Uint8>(b(gRng));
    c.a = static_cast<Uint8>(a(gRng));

    return c;
}

inline void to_json(json& j, const particleColorRange& pcr) {
   j = json::object();

    j["start"] = pcr.start;
    j["end"] = pcr.end;
}

inline void from_json(const json& j, particleColorRange& pcr) {
    j.at("start").get_to(pcr.start);
    j.at("end").get_to(pcr.end);
}