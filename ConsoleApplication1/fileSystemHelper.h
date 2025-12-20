#pragma once
#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

fs::path getStormDefaultsPath() {
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
