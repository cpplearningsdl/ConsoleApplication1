#pragma once
#include "json.hpp"

using json = nlohmann::ordered_json;

struct lightningGeneratorConfig {
    float displacement = 30.0f;
    float displacementFalloff = 0.5f;
    int recursionDepth = 6;

    float branchChance = 0.25f;
    int maxBranches = 3;

    float jitterAmplitude = 1.5f;

    float baseWidth = 4.0f;
};
inline void to_json(json& j, const lightningGeneratorConfig& c) {
    j = {
        { "displacement", c.displacement },
        { "displacementFalloff", c.displacementFalloff },
        { "recursionDepth", c.recursionDepth },
        { "branchChance", c.branchChance },
        { "maxBranches", c.maxBranches },
        { "jitterAmplitude", c.jitterAmplitude },
        { "baseWidth", c.baseWidth }
    };
}

inline void from_json(const json& j, lightningGeneratorConfig& c) {
    if (j.contains("displacement"))
        c.displacement = j.at("displacement").get<float>();

    if (j.contains("displacementFalloff"))
        c.displacementFalloff = j.at("displacementFalloff").get<float>();

    if (j.contains("recursionDepth"))
        c.recursionDepth = j.at("recursionDepth").get<int>();

    if (j.contains("branchChance"))
        c.branchChance = j.at("branchChance").get<float>();

    if (j.contains("maxBranches"))
        c.maxBranches = j.at("maxBranches").get<int>();

    if (j.contains("jitterAmplitude"))
        c.jitterAmplitude = j.at("jitterAmplitude").get<float>();

    if (j.contains("baseWidth"))
        c.baseWidth = j.at("baseWidth").get<float>();

    // ---- sanity clamps ----
    c.displacement = std::max(0.0f, c.displacement);
    c.displacementFalloff = std::clamp(c.displacementFalloff, 0.1f, 1.0f);
    c.recursionDepth = std::clamp(c.recursionDepth, 1, 10);
    c.branchChance = std::clamp(c.branchChance, 0.0f, 1.0f);
    c.maxBranches = std::max(0, c.maxBranches);
    c.jitterAmplitude = std::max(0.0f, c.jitterAmplitude);
    c.baseWidth = std::max(0.1f, c.baseWidth);
}
