#pragma once
#include "json.hpp"
#include "rainStormconfig.h"

using json = nlohmann::ordered_json;

struct rainStormDef {
    std::string id;
    rainStormConfig config;
};


 
inline void to_json(json& j, const rainStormDef& f) {
    j = json::object();

    j["id"] = f.id;
    j["config"] = f.config;

}

inline void from_json(const  json& j, rainStormDef& f) {
    j.at("id").get_to(f.id);
    j.at("config").get_to(f.config);
}