#pragma once

#include <string>
#include <algorithm> 
#include "fireStormSpawnParams.h"
#include "fireStormSizeParams.h"
#include "fireStormFireLineParams.h"
#include "fireStormEmberParams.h"
#include "fireColorProfile.h"
#include "SDL_fpoint_Json.h"
#include "SDL_Color_json.h"

#include "json.hpp"

using json = nlohmann::ordered_json;

 
// ------------------------------------------------------------
// Fire storm configuration (definition-level)
// ------------------------------------------------------------
struct fireStormConfig {
    float stormDuration = 2.0f;
    fireStormSpawnParams spawnParams;
    fireStormSizeParams sizeParams; 
    fireStormFireLineParams fireLineParams;
    fireStormEmberParams emberParams; 
    fireColorProfile colorProfile;
};

// ------------------------------------------------------------
// JSON serialization
// ------------------------------------------------------------
inline void to_json(json& j, const fireStormConfig& c) {
    j = json::object();
     
    j["stormDuration"] = c.stormDuration;  
    j["spawnParams"] = c.spawnParams;
    j["sizeParams"] = c.sizeParams;
    j["fireLineParams"] = c.fireLineParams;
    j["emberParams"] = c.emberParams;
    j["colorProfile"] = c.colorProfile;
}

inline void from_json(const json& j, fireStormConfig& c) {
    c = fireStormConfig{};

    if (j.contains("stormDuration"))
        c.stormDuration = j.at("stormDuration").get<float>();  

    if (j.contains("spawnParams"))
        c.spawnParams = j.at("spawnParams").get<fireStormSpawnParams>();

    if (j.contains("sizeParams"))
        c.sizeParams = j.at("sizeParams").get<fireStormSizeParams>();

    if (j.contains("fireLineParams"))
        c.fireLineParams = j.at("fireLineParams").get<fireStormFireLineParams>();
     

    if (j.contains("emberParams"))  
        c.emberParams = j.at("emberParams").get<fireStormEmberParams>();

    if (j.contains("colorProfile"))
        c.colorProfile = j.at("colorProfile").get<fireColorProfile>();


    c.stormDuration = std::max(0.0f, c.stormDuration);  
}