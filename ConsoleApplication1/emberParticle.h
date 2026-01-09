#pragma once
#include <SDL3/SDL.h>
#include "SDL_Fpoint_json.h"
#include "SDL_Color_json.h"
#include "emberMovementEnum.h"
#include "json.hpp"

using json = nlohmann::ordered_json;

struct emberParticle {
    SDL_FPoint pos;
    SDL_FPoint velocity;

    float lifetime;
    float age;
    float size;

    emberMovementEnum movement;
    SDL_Color color;

    void update(float dt);
};

inline void to_json(json& j, const emberParticle& ep) {
    j["pos"] = ep.pos;
    j["velocity"] = ep.velocity;
    j["lifetime"] = ep.lifetime;
    j["age"] = ep.age;
    j["size"] = ep.size;
    j["movement"] = ep.movement;
    j["color"] = ep.color;
}
 
 inline void from_json(const json & j, emberParticle & e) {
        // Required
        e.pos = j.at("pos").get<SDL_FPoint>();
        e.velocity = j.at("velocity").get<SDL_FPoint>();
        e.lifetime = j.at("lifetime").get<float>();
        e.size = j.at("size").get<float>();
        e.movement = j.at("movement").get<emberMovementEnum>();

        // runtime
        e.age = j.value("age", 0.0f);
        e.color = j.value("color", SDL_Color{ 255, 255, 255, 255 });
 } 