#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_fpoint_Json.h"
#include "SDL_Color_json.h"
#include "fireLineParams.h"

using json = nlohmann::ordered_json;

struct fireLine {
    SDL_FPoint start;
    SDL_FPoint end;

    float targetLength;
    float currentLength;

    SDL_FPoint dir;         // normalized, mostly upward

    float swayPhase;
    float lengthPhase;

    float colorT;//IS THIS EVEN BEING USED?!
    float colorDir;

    void update(float dt, const fireLineParams& cfg);
};

 
inline void to_json(json& j, const fireLine& p) {
    j = json::object();

    j["start"] = p.start;
    j["end"] = p.end; 
   
    j["targetLength"] = p.targetLength;
    j["currentLength"] = p.currentLength;  
    
    j["dir"] = p.dir;
    j["swayPhase"] = p.swayPhase;
    j["lengthPhase"] = p.lengthPhase;

    j["colorT"] = p.colorT;
    j["colorDir"] = p.colorDir;
 
}

inline void from_json(const json& j, fireLine& p) {
    j.at("start").get_to(p.start);
    j.at("end").get_to(p.end);

    j.at("targetLength").get_to(p.targetLength);
    j.at("currentLength").get_to(p.currentLength); 
    
    j.at("dir").get_to(p.dir);
    j.at("swayPhase").get_to(p.swayPhase);
    j.at("lengthPhase").get_to(p.lengthPhase);

    j.at("colorT").get_to(p.colorT);
    j.at("colorDir").get_to(p.colorDir);

}