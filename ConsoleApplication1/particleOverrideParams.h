#pragma once
#include "particleSpawnParams.h"
#include "particleMotionParams.h" 

struct particleOverrides {
    bool overrideSpawn = false;
    particleSpawnParams spawn = { particleSpawnType::POINT, -100.0f, -100.0f, 0.0f, 0.0f };

    bool overrideMotion = false;
    particleMotionParams motion {particleMotionType::RANDOM_DIRECTION, 0.0f, 0.0f};


    bool overrideOrigin = false;
    SDL_FPoint origin = { -100.0f, -100.0f };

    bool overrideRadiusInner = false;
    float radiusInner = 0.0f;

    bool overrideRadiusOuter = false;
    float radiusOuter = 0.0f;
};


inline void to_json(json& j, const particleOverrides& s) {
    j = json::object();

    j["overrideSpawn"] = s.overrideSpawn;
    j["spawn"] = s.spawn;

    j["overrideMotion"] = s.overrideMotion;
    j["motion"] = s.motion;

    j["overrideOrigin"] = s.overrideOrigin;
    j["origin"] = s.origin;

    j["overrideRadiusInner"] = s.overrideRadiusInner;
    j["radiusInner"] = s.radiusInner;

    j["overrideRadiusOuter"] = s.overrideRadiusOuter;
    j["radiusOuter"] = s.radiusOuter;

}

inline void from_json(const json& j, particleOverrides& s) {
    j.at("overrideSpawn").get_to(s.overrideSpawn);
    j.at("spawn").get_to(s.spawn);

    j.at("overrideMotion").get_to(s.overrideMotion);
    j.at("motion").get_to(s.motion);

    j.at("overrideOrigin").get_to(s.motion);
    j.at("origin").get_to(s.origin);

    j.at("overrideRadiusInner").get_to(s.overrideRadiusInner);
    j.at("radiusInner").get_to(s.radiusInner);

    j.at("overrideRadiusOuter").get_to(s.overrideRadiusOuter);
    j.at("radiusOuter").get_to(s.radiusOuter);
}