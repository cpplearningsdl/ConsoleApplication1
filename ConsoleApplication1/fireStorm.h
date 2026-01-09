#pragma once
#include "json.hpp"
#include "fire.h"
#include "fireStormDef.h"

using json = nlohmann::ordered_json;

struct fireStorm {
    fireStormDef def;
    std::vector<fire> fires;

    void update(float dt);
    void render(SDL_Renderer* renderer) const;
};

inline void to_json(json& j, const fireStorm& f) {
    j = json::object();

    j["def"] = f.def;
    j["fires"] = f.fires;
}

inline void from_json(const json& j, fireStorm& f) {
    j.at("def").get_to(f.def);
    f.fires = j.value("fires", std::vector<fire>{});
}