#pragma once
#include "SDL3/SDL.h"
#include "SDL_Color_Json.h"
#include "json.hpp"

using json = nlohmann::ordered_json;

struct particleColorRange {
    SDL_Color min;
    SDL_Color max;
};


inline void to_json(json& j, const particleColorRange& pcr) {
   j = json::object();

    j["min"] = pcr.min;
    j["max"] = pcr.max;
}

inline void from_json(const json& j, particleColorRange& pcr) {
    j.at("min").get_to(pcr.min);
    j.at("max").get_to(pcr.max);
}