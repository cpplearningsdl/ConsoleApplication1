#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "particleMotionType.h"
#include "SDL_Fpoint_json.h"
#include "SDL_Color_Json.h"

struct particle {
    particleMotionType motionType;
    SDL_FPoint position = { -100.0f, -100.0f };
    SDL_FPoint velocity = { 0.0f, 0.0f };

    size_t currentStep = 0;
    float nextMotionTime = 0.0f;

    float orbitAngle = 0.0f;
    float orbitRadius = 0.0f;

    SDL_Color color = { 0, 0, 0, 0 }; 
    SDL_Color colorStart = { 0, 0, 0, 0 };
    SDL_Color colorEnd = { 0, 0, 0, 0 };

    float colorPhase = 0.0f;
    float colorSpeed = 1.0f;

    float size = 0.0f;

    float age = 0.0f;
    float lifetime = 0.0f;

    bool isAlive() const { return age < lifetime;}
};


inline void to_json(json& j, const particle& p) {
    j = json::object(); 
    j["motionType"] = p.motionType;
    j["position"] = p.position;
    j["velocity"] = p.velocity;
    j["currentStep"] = p.currentStep;
    j["nextMotionTime"] = p.nextMotionTime;
    j["orbitAngle"] = p.orbitAngle;
    j["orbitRadius"] = p.orbitRadius;
    j["color"] = p.color;
    j["colorStart"] = p.colorStart;
    j["colorEnd"] = p.colorEnd;
    j["colorPhase"] = p.colorPhase;
    j["colorSpeed"] = p.colorSpeed;
    j["size"] = p.size;
    j["age"] = p.age;
    j["lifetime"] = p.lifetime; 
}

inline void from_json(const json& j, particle& p) {
    j.at("motionType").get_to(p.motionType);
    j.at("position").get_to(p.position);
    j.at("velocity").get_to(p.velocity);
    j.at("currentStep").get_to(p.currentStep);
    j.at("nextMotionTime").get_to(p.nextMotionTime);
    j.at("orbitAngle").get_to(p.orbitAngle);
    j.at("orbitRadius").get_to(p.orbitRadius);
    j.at("color").get_to(p.color);
    j.at("colorStart").get_to(p.colorStart);
    j.at("colorEnd").get_to(p.colorEnd);
    j.at("colorPhase").get_to(p.colorPhase);
    j.at("colorSpeed").get_to(p.colorSpeed);
    j.at("size").get_to(p.size);
    j.at("age").get_to(p.age);
    j.at("lifetime").get_to(p.lifetime);
}