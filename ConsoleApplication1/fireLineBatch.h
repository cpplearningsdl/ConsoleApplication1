#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_fpoint_Json.h"
#include "SDL_Color_json.h"

using json = nlohmann::ordered_json;


struct fireLineBatch {
    std::vector<SDL_FPoint> starts;
    std::vector<SDL_FPoint> ends;
    std::vector<SDL_Color> colors;

    void clear() {
        starts.clear();
        ends.clear();
        colors.clear();
    }
};

inline void to_json(json& j, const fireLineBatch& b) {
    j = json{
        { "starts", b.starts },
        { "ends",  b.ends } ,
        {"colors", b.colors }
    };
}

inline void from_json(const json& j, fireLineBatch& b) {
    b.starts = j.at("starts").get<std::vector<SDL_FPoint>>();
    b.ends = j.at("ends").get<std::vector<SDL_FPoint>>();
    b.colors = j.at("colors").get<std::vector<SDL_Color>>();
}
