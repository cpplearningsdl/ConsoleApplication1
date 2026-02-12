#pragma once
#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

inline fs::path getStormDefaultsPath() {
    char* userProfile = nullptr;
    size_t len = 0;

    if (_dupenv_s(&userProfile, &len, "USERPROFILE") != 0 || !userProfile) {
        return {};
    }

    fs::path basePath(userProfile);
    free(userProfile);

    basePath /= "AppData";
    basePath /= "Roaming";
    basePath /= "ConsoleApplication1";
    basePath /= "stormDefaults";

    return basePath;
}
inline fs::path getFireStormDefaultsPath() {
    char* userProfile = nullptr;
    size_t len = 0;

    if (_dupenv_s(&userProfile, &len, "USERPROFILE") != 0 || !userProfile) {
        return {};
    }

    fs::path basePath(userProfile);
    free(userProfile);

    basePath /= "AppData";
    basePath /= "Roaming";
    basePath /= "ConsoleApplication1";
    basePath /= "fireStormDefaults";

    return basePath;
}

inline fs::path getParticleStormDefaultsPath() {
    char* userProfile = nullptr;
    size_t len = 0;

    if (_dupenv_s(&userProfile, &len, "USERPROFILE") != 0 || !userProfile) {
        return {};
    }

    fs::path basePath(userProfile);
    free(userProfile);

    basePath /= "AppData";
    basePath /= "Roaming";
    basePath /= "ConsoleApplication1";
    basePath /= "particleStormDefaults";

    return basePath;
}

inline fs::path getRainStormDefaultsPath() {
    char* userProfile = nullptr;
    size_t len = 0;

    if (_dupenv_s(&userProfile, &len, "USERPROFILE") != 0 || !userProfile) {
        return {};
    }

    fs::path basePath(userProfile);
    free(userProfile);

    basePath /= "AppData";
    basePath /= "Roaming";
    basePath /= "ConsoleApplication1";
    basePath /= "rainStormDefaults";

    return basePath;
}