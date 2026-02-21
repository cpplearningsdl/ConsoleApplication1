#pragma once
#include <vector>
#include <string>
#include "json.hpp" 

using json = nlohmann::ordered_json;

struct rainStormSequence {
    std::string nextStormId; 
    bool continueSequence = false;
};

inline void to_json(json& j, const rainStormSequence& seq) { 
    j = json::object();
    j["nextStormId"] = seq.nextStormId; 
    j["continueSequence"] = seq.continueSequence;
}

inline void from_json(const json& j, rainStormSequence& seq) {
    seq.nextStormId = j.value("nextStormId", std::string{}); 
    seq.continueSequence = j.value("continueSequence", bool{});
}