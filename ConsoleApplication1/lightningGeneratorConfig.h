#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

struct lightningGeneratorConfig {
    float displacement = 30.0f;
    float displacementFalloff = 0.5f;
    int recursionDepth = 6;

 
    float jitterAmplitude = 1.5f;

    float baseWidth = 4.0f;
    int maxNodes = 0;       // 0 = unlimited
    int maxSegments = 0;    // 0 = unlimited
};
inline void to_json(json& j, const lightningGeneratorConfig& c) {
    j = {
        { "displacement", c.displacement },
        { "displacementFalloff", c.displacementFalloff },
        { "recursionDepth", c.recursionDepth },
        { "jitterAmplitude", c.jitterAmplitude },
        { "baseWidth", c.baseWidth },
        { "maxNodes", c.maxNodes },
        { "maxSegments", c.maxSegments }
    };
}

inline void from_json(const json& j, lightningGeneratorConfig& c) {
    if (j.contains("displacement"))
        c.displacement = j.at("displacement").get<float>();

    if (j.contains("displacementFalloff"))
        c.displacementFalloff = j.at("displacementFalloff").get<float>();

    if (j.contains("recursionDepth"))
        c.recursionDepth = j.at("recursionDepth").get<int>();

 

    if (j.contains("jitterAmplitude"))
        c.jitterAmplitude = j.at("jitterAmplitude").get<float>();

    if (j.contains("baseWidth"))
        c.baseWidth = j.at("baseWidth").get<float>();

    if (j.contains("maxNodes"))
        c.maxNodes = j.at("maxNodes").get<int>();

    if (j.contains("maxSegments"))
        c.maxSegments = j.at("maxSegments").get<int>();
     
    c.displacement = std::max(0.0f, c.displacement);
    c.displacementFalloff = std::clamp(c.displacementFalloff, 0.1f, 1.0f);
    c.recursionDepth = std::clamp(c.recursionDepth, 1, 10);
 
    c.jitterAmplitude = std::max(0.0f, c.jitterAmplitude);
    c.baseWidth = std::max(0.1f, c.baseWidth);
    c.maxNodes = std::max(0, c.maxNodes);
    c.maxSegments = std::max(0, c.maxSegments);
}
