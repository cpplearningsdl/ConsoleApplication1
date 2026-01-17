#pragma once
#include "json.hpp"
#include "fireLineParams.h"

using json = nlohmann::ordered_json;

struct fireStormFireLineParams {
    fireLineParams primary;
    fireLineParams secondary;
};

inline void to_json(json& j, const fireStormFireLineParams& f) {
    j = json::object();

    j["primary"] = f.primary;
    j["secondary"] = f.secondary;
}

inline void from_json(const json& j, fireStormFireLineParams& f) {
    if (j.contains("primary"))
        j.at("primary").get_to(f.primary);

    if (j.contains("secondary"))
        j.at("secondary").get_to(f.secondary);
}