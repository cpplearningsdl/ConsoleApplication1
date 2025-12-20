#pragma once
#include <unordered_map>
#include <algorithm>
#include "ambianceSaveData.h"
#include "ambiance.h" 
#include "weatherType.h"
#include "dayDivision.h"

#include <SDL3/SDL.h> 

class ambianceManager {
public:
    ambianceManager() = default;

    ambiance& getAmbiance() { return amb; }
    const ambiance& getAmbiance() const { return amb; }

    void setDayLength(float seconds); 
    void setWeather(weatherType w); 
    void setProfile(weatherType w, const dayDivision& profile);

     void update(float deltaTime);
     ambianceSaveData serialize() const;
     void deserialize(const ambianceSaveData& data);
private:
    ambiance amb;

    float dayLength = 300.0f; // seconds
    float timeOfDay = 0.0f;

    std::unordered_map<weatherType, dayDivision> profiles;

    Uint8 evaluateDarkness(float t, const dayDivision& d);

    static Uint8 lerp(Uint8 a, Uint8 b, float t) {
        t = std::clamp(t, 0.0f, 1.0f);
        return static_cast<Uint8>(a + (b - a) * t);
    }
};

