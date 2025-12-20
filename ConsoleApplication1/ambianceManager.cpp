#include "ambianceManager.h"
#include "ambianceSaveData.h"
#include "ambiance.h"
#include "dayDivision.h"
#include "weatherType.h"
#include "logManager.h"



void ambianceManager::setDayLength(float seconds) {
    dayLength = seconds;
}

void ambianceManager::setWeather(weatherType w) {
    amb.weather = w;
}

void ambianceManager::setProfile(weatherType w, const dayDivision& profile) {
    profiles[w] = profile;
}

void ambianceManager::update(float deltaTime) {
    if (!amb.enabled || dayLength <= 0.0f)
        return;

    // Advance time
    timeOfDay += deltaTime;
    if (timeOfDay >= dayLength)
        timeOfDay -= dayLength;

    float t = timeOfDay / dayLength; // 0–1
    amb.timeNormalized = t;

    const dayDivision& d = profiles[amb.weather];
    amb.setDarkness(evaluateDarkness(t, d));
}


Uint8 ambianceManager::evaluateDarkness(float t, const dayDivision& d) {
    float s0 = d.sunrise;
    float s1 = s0 + d.day;
    float s2 = s1 + d.sunset;

    if (t < s0) {
        // Sunrise
        return lerp(d.nightDarkness, d.sunriseDarkness, t / s0);
    }
    else if (t < s1) {
        // Day
        return lerp(d.sunriseDarkness, d.dayDarkness,
            (t - s0) / d.day);
    }
    else if (t < s2) {
        // Sunset
        return lerp(d.dayDarkness, d.sunsetDarkness,
            (t - s1) / d.sunset);
    }
    else {
        // Night
        return lerp(d.sunsetDarkness, d.nightDarkness,
            (t - s2) / d.night);
    }
}

ambianceSaveData ambianceManager::serialize() const {
    ambianceSaveData out;
    out.dayLength = dayLength;
    out.timeOfDay = timeOfDay;
    out.amb = amb;
    out.profiles = profiles;
    return out;
}

void ambianceManager::deserialize(const ambianceSaveData& data) {
    dayLength = data.dayLength;
    timeOfDay = data.timeOfDay;
    amb = data.amb;
    profiles = data.profiles;
}