#pragma once
#include <vector>
#include "json.hpp"
#include "particleMotionParams.h"

    struct particleMotionSequence {

        std::vector<particleMotionParams> steps;
    };

inline void to_json(json& j, const particleMotionSequence& seq) {
  
    j = json::object();
    j["steps"] = seq.steps;
}

inline void from_json(const json& j, particleMotionSequence& seq) {

    seq.steps = j.value("steps", std::vector<particleMotionParams>{});
}
