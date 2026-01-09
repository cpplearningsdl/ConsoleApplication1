#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

struct fireStormSizeParams { 
    float sizeMin = 1.0f;
    float sizeMax = 1.0f;

    float baseWidthMultiplier = 0.4f;

    int primaryLinesMin = 6;
    int primaryLinesMax = 10;

    int secondaryLinesMin = 10;
    int secondaryLinesMax = 18;

};

inline void to_json(json& j, const fireStormSizeParams& c) {
    j = json::object(); 

    j["sizeMin"] = c.sizeMin;
    j["sizeMax"] = c.sizeMax;
    j["baseWidthMultiplier"] = c.baseWidthMultiplier;

    j["primaryLinesMin"] = c.primaryLinesMin;
    j["primaryLinesMax"] = c.primaryLinesMax;
    j["secondaryLinesMin"] = c.secondaryLinesMin;
    j["secondaryLinesMax"] = c.secondaryLinesMax;

 
}

inline void from_json(const json& j, fireStormSizeParams& c) {
       
    if (j.contains("sizeMin"))
        c.sizeMin = j.at("sizeMin").get<float>();

    if (j.contains("sizeMax"))
        c.sizeMax = j.at("sizeMax").get<float>();

    if (j.contains("baseWidthMultiplier"))
        c.baseWidthMultiplier = j.at("baseWidthMultiplier").get<float>();

    if (j.contains("primaryLinesMin"))
        c.primaryLinesMin = j.at("primaryLinesMin").get<int>();

    if (j.contains("primaryLinesMax"))
        c.primaryLinesMax = j.at("primaryLinesMax").get<int>();

    if (j.contains("secondaryLinesMin"))
        c.secondaryLinesMin = j.at("secondaryLinesMin").get<int>();

    if (j.contains("secondaryLinesMax"))
        c.secondaryLinesMax = j.at("secondaryLinesMax").get<int>();
      
}