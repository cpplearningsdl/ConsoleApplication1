#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

struct rainSizeParams {
    float lengthMin = 8.0f;
    float lengthMax = 16.0f;

    int thickness = 1; // NOT IMPLEMENTED ** NEED TO ADJUST ESTIMATED VECTOR SIZE FOR RESERVING ON STORM CREATION!! multiply by thickness s.primaryLineBatch.reserve(expectedPrimary * thickness * 2);
};

inline void to_json(json& j, const rainSizeParams& p) {
    j = json::object();
    j["lengthMin"] = p.lengthMin;
    j["lengthMax"] = p.lengthMax;
    j["thickness"] = p.thickness; 
}

inline void from_json(const json& j, rainSizeParams& p) {
    j.at("lengthMin").get_to(p.lengthMin);
    j.at("lengthMax").get_to(p.lengthMax);
    j.at("thickness").get_to(p.thickness); 
}