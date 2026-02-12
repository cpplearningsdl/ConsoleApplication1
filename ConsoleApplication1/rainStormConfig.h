#pragma once
#include "json.hpp"
#include "rainStormSpawnParams.h" 
#include "rainStormColorParams.h"
#include "rainStormKillParams.h"
#include "rainStormWindParams.h"
#include "rainSizeParams.h"
#include "rainVelocityParams.h"

struct rainStormConfig {
    float stormDuration = 0.0f;   // 0 = infinite
    rainStormSpawnParams spawnParams; 
    rainKillParams killParams;
    rainWindParams windParams;
    rainSizeParams sizeParams;
    rainVelocityParams velocityParams;
    rainStormColorParams colors; 
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
     
    c.stormDuration = std::max(0.0f, c.stormDuration);
}