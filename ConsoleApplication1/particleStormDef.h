#pragma once
#include <string>
#include "json.hpp"
#include "particleStormConfig.h"



using json = nlohmann::ordered_json;

struct particleStormDef {
	std::string id;
	particleStormConfig config;
};


inline void to_json(json& j, const particleStormDef& f) {
    j = json::object();

    j["id"] = f.id;
    j["config"] = f.config;

}

inline void from_json(const  json& j, particleStormDef& f) {
    j.at("id").get_to(f.id);
    j.at("config").get_to(f.config);
}