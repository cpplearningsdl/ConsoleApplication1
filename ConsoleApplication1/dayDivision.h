#pragma once
#include <SDL3/SDL.h>
#include "json.hpp"

using json = nlohmann::ordered_json;

struct dayDivision {
    // Percentages of a full day
    float sunrise = 0.15f;
    float day = 0.35f;
    float sunset = 0.15f;
    float night = 0.35f;

    // Darkness levels for each phase
    Uint8 sunriseDarkness = 80;
    Uint8 dayDarkness = 0;
    Uint8 sunsetDarkness = 120;
    Uint8 nightDarkness = 180;
};
// ---------------- JSON ----------------

inline void to_json(json& j, const dayDivision& d) {
    j = json{
        { "sunrise", d.sunrise },
        { "day",     d.day },
        { "sunset",  d.sunset },
        { "night",   d.night },

        { "sunriseDarkness", d.sunriseDarkness },
        { "dayDarkness",     d.dayDarkness },
        { "sunsetDarkness",  d.sunsetDarkness },
        { "nightDarkness",   d.nightDarkness }
    };
}

inline void from_json(const json& j, dayDivision& d) {
    // Percentages
    d.sunrise = j.value("sunrise", d.sunrise);
    d.day = j.value("day", d.day);
    d.sunset = j.value("sunset", d.sunset);
    d.night = j.value("night", d.night);

    // Darkness
    d.sunriseDarkness = j.value("sunriseDarkness", d.sunriseDarkness);
    d.dayDarkness = j.value("dayDarkness", d.dayDarkness);
    d.sunsetDarkness = j.value("sunsetDarkness", d.sunsetDarkness);
    d.nightDarkness = j.value("nightDarkness", d.nightDarkness);

}