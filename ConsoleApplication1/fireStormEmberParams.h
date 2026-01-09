#pragma once
#include "emberMovementEnum.h"

struct fireStormEmberParams {
    bool smoke = false; 
    int embersPerFireMin = 6;
    int embersPerFireMax = 14; 
    emberMovementEnum emberMovement = emberMovementEnum::RISE; 
};


inline void to_json(json& j, const fireStormEmberParams& c) {
    j = json::object();

    j["smoke"] = c.smoke;
    j["embersPerFireMin"] = c.embersPerFireMin;
    j["embersPerFireMax"] = c.embersPerFireMax;
    j["emberMovement"] = c.emberMovement;

}

inline void from_json(const json& j, fireStormEmberParams& c) {
     
    if (j.contains("smoke"))
        c.smoke = j.at("smoke").get<bool>(); 
 
    if (j.contains("embersPerFireMin"))
        c.embersPerFireMin = j.at("embersPerFireMin").get<int>();

    if (j.contains("embersPerFireMax"))
        c.embersPerFireMax = j.at("embersPerFireMax").get<int>();

    if (j.contains("emberMovement"))
        c.emberMovement = j.at("emberMovement").get<emberMovementEnum>();

}