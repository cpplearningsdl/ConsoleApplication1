#pragma once
#include "json.hpp"
#include "fire.h"
#include "fireStormDef.h"

using json = nlohmann::ordered_json;

struct fireStorm {
    fireStormDef def;
    float age = 0.0f;
    float spreadTimer = 0.0f;
    std::vector<fire> fires;

    void update(float dt);
    void spread(float dt);
    void render(SDL_Renderer* renderer) const;
};

inline void to_json(json& j, const fireStorm& f) {
    j = json::object();

    j["def"] = f.def;
    j["age"] = f.age;
    j["spreadTimer"] = f.spreadTimer;
    j["fires"] = f.fires;
}

inline void from_json(const json& j, fireStorm& f) {
    j.at("def").get_to(f.def);
    j.at("age").get_to(f.age);
    j.at("spreadTimer").get_to(f.spreadTimer);
    f.fires = j.value("fires", std::vector<fire>{});  
}