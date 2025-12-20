#pragma once
#include <unordered_map>
#include "json.hpp"
#include "ambiance.h"
#include "dayDivision.h"
#include "weatherType.h"

using json = nlohmann::ordered_json;


struct ambianceSaveData {
    float dayLength;
    float timeOfDay;
    weatherType currentWeather;
    ambiance amb;
    std::unordered_map<weatherType, dayDivision> profiles;
};

inline void to_json(json& j, const ambianceSaveData& d) {
    j = {
        {"dayLength", d.dayLength},
        {"timeOfDay", d.timeOfDay},
        {"ambiance", d.amb},
        {"weatherType", d.currentWeather},
        {"profiles", d.profiles}
    };
}

inline void from_json(const json& j, ambianceSaveData& d) {
    j.at("dayLength").get_to(d.dayLength);
    j.at("timeOfDay").get_to(d.timeOfDay);
    j.at("ambiance").get_to(d.amb);
    j.at("weatherType").get_to(d.currentWeather);
    j.at("profiles").get_to(d.profiles);
}