#pragma once
#include "json.hpp"
 
using json = nlohmann::ordered_json;

enum class emberMovementEnum {
    RISE,        // slow upward drift (heat lift)
    RISEANDFAN,  // upward + lateral dispersion
    ARC,         // ballistic arc (embers thrown from fire)
    DRIFT,       // slow, almost weightless (smoke-like) 
};

inline void to_json(json& j, const emberMovementEnum& fst) {
    switch (fst) {
    case emberMovementEnum::RISE:   j = "RISE";   break;
    case emberMovementEnum::RISEANDFAN: j = "RISEANDFAN"; break;
    case emberMovementEnum::ARC: j = "ARC"; break;
    case emberMovementEnum::DRIFT: j = "DRIFT"; break;
    default:
        j = "DRIFT";
        break;
    }
}

inline void from_json(const json& j, emberMovementEnum& t){
    const std::string s = j.get<std::string>();

    if (s == "RISE")                  t = emberMovementEnum::RISE;
    else if (s == "RISEANDFAN")       t = emberMovementEnum::RISEANDFAN;
    else if (s == "ARC")              t = emberMovementEnum::ARC;
    else if (s == "DRIFT")            t = emberMovementEnum::DRIFT;
 }
