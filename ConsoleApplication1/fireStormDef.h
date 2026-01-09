#pragma once 
#include <string>
#include <SDL3/SDL.h>
#include "json.hpp"
#include "fireStormConfig.h" 

using json = nlohmann::ordered_json;

struct fireStormDef {
    std::string id;

    fireStormConfig config;  
};

inline void to_json(json& j, const fireStormDef& f) {
    j = json::object();

    j["id"] = f.id;
    j["config"] = f.config;

}

inline void from_json(const  json& j, fireStormDef& f) {
    j.at("id").get_to(f.id);
    j.at("config").get_to(f.config);
}