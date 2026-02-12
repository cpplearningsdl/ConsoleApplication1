#pragma once
#include "rainStormSpawnParams.h"
#include "json.hpp"

struct rainOverrideParams {
	bool overrideSpawn = false;
	rainStormSpawnParams spawnOverrides = {}; 
};


inline void to_json(json& j, const rainOverrideParams& s) {
    j = json::object();

    j["overrideSpawn"] = s.overrideSpawn;
    j["spawnOverrides"] = s.spawnOverrides;  
}

inline void from_json(const json& j, rainOverrideParams& s) {
    j.at("overrideSpawn").get_to(s.overrideSpawn);
    j.at("spawnOverrides").get_to(s.spawnOverrides);
     
}