#pragma once
#include "json.hpp"
#include "rainStormSpawnParams.h" 
#include "rainStormColorParams.h"
#include "rainStormKillParams.h"
#include "rainStormWindParams.h"
#include "rainSizeParams.h"
#include "rainVelocityParams.h"
#include "rainStormSequence.h"
#include "rainStormEmitParams.h"
#include "rainStormSizeAnimationSequence.h"

struct rainStormConfig {
    float stormDuration = 0.0f;   // 0 = infinite
    rainStormSpawnParams spawnParams; 
    rainKillParams killParams;
    rainWindParams windParams;
    rainSizeParams sizeParams;
    rainVelocityParams velocityParams;
    rainStormColorParams colors; 
    rainStormSequence sequence;
    rainEmitParams emitParams;
    rainStormSizeAnimationSequence sizeAnimationSequence;
};


inline void to_json(json& j, const rainStormConfig& c) {
    j = json::object();

    j["stormDuration"] = c.stormDuration;
    j["spawnParams"] = c.spawnParams; 
    j["killParams"] = c.killParams;
    j["windParams"] = c.windParams;
    j["sizeParams"] = c.sizeParams;
    j["velocityParams"] = c.velocityParams;
    j["colors"] = c.colors;
    j["sequence"] = c.sequence;
    j["emitParams"] = c.emitParams;
    j["sizeAnimationSequence"] = c.sizeAnimationSequence;
}

inline void from_json(const json& j, rainStormConfig& c) {
    c = rainStormConfig{};

    if (j.contains("stormDuration"))
        c.stormDuration = j.at("stormDuration").get<float>();
  
    if (j.contains("spawnParams"))
        c.spawnParams = j.at("spawnParams").get<rainStormSpawnParams>();
     
    if (j.contains("killParams"))
        c.killParams = j.at("killParams").get<rainKillParams>();

    if (j.contains("windParams"))
        c.windParams = j.at("windParams").get<rainWindParams>();

    if (j.contains("sizeParams"))
        c.sizeParams = j.at("sizeParams").get<rainSizeParams>();

    if (j.contains("velocityParams"))
        c.velocityParams = j.at("velocityParams").get<rainVelocityParams>();
    
    if (j.contains("colors"))
        c.colors = j.at("colors").get<rainStormColorParams>();
     
    if (j.contains("sequence"))
        c.sequence = j.at("sequence").get<rainStormSequence>();

    if (j.contains("emitParams"))
        c.emitParams = j.at("emitParams").get<rainEmitParams>();

    if (j.contains("sizeAnimationSequence"))
        c.sizeAnimationSequence = j.at("sizeAnimationSequence").get<rainStormSizeAnimationSequence>();

    c.stormDuration = std::max(0.0f, c.stormDuration);
}