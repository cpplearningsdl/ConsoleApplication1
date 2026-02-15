#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "json.hpp"
#include "drop.h"
#include "rainStormDef.h"
#include "rainOverrideParams.h"
#include "rainWindState.h"
#include "rainVelocityState.h"

using json = nlohmann::ordered_json;

struct rainStorm {

    rainStormDef def;
    rainOverrideParams overrideParams = {};

    rainStormSpawnParams actualSpawnParams; 

    rainWindState     wind;
    rainVelocityState velocity;

    //float nextmotiontime = 0.0f;
    //int motionstep = 0;
    //motiontimingmode timingmode = motiontimingmode::per_storm;

    std::vector<drop> drops;

    float age = 0.0f;
    float emitAccumulator = 0.0f;


    void update(float t);
    void updateActualParams();
    void resolveSpawnOverride();
    void updateDrops(float dt); 
    void resetDrop(drop& d);
    bool isOutsideKillVolume(const SDL_FPoint& p, const rainKillParams& k);
};


inline void to_json(json& j, const rainStorm& s) {
    j = json::object();

    j["def"] = s.def;
    j["overrideParams"] = s.overrideParams;
    j["actualSpawnParams"] = s.actualSpawnParams;
    j["drops"] = s.drops;
    j["age"] = s.age;
    j["emitAccumulator"] = s.emitAccumulator;  
}

inline void from_json(const json& j, rainStorm& s) {
    j.at("def").get_to(s.def);
    j.at("overrideParams").get_to(s.overrideParams);
    j.at("actualSpawnParams").get_to(s.actualSpawnParams); 
    j.at("drops").get_to(s.drops);
    j.at("age").get_to(s.age);
    j.at("emitAccumulator").get_to(s.emitAccumulator);
    s.drops = j.value("drops", std::vector<drop>{}); 

}