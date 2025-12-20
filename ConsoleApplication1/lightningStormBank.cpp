#pragma once
#include <vector>
#include <string> 
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include "json.hpp" 
#include "logManager.h"
#include "lightningStormBank.h"
#include "fileSystemHelper.h"

using json = nlohmann::ordered_json;

lightningStormBank::lightningStormBank() {
    loadFromDirectory(getStormDefaultsPath());
}
lightningStormBank::~lightningStormBank() {
    defs.clear();
}
bool lightningStormBank::loadFromDirectory(const std::filesystem::path& path) {
    if (!fs::exists(path) || !fs::is_directory(path)) { 
        logManager::logThis("Failed to load stormBank: Path or Directory is missing; ", path.generic_string());
        return false;
    } 
    for (const auto& entry : fs::directory_iterator(path)) {
        if (!entry.is_regular_file())
            continue;

        if (entry.path().extension() != ".json")
            continue;

        std::ifstream file(entry.path());
        if (!file.is_open())
            continue;

        nlohmann::json j;
        file >> j;

        lightningStormDef def;

        // ---- Required ----
        def.id = j.at("id").get<std::string>();

        // ---- Optional anchors ----
        if (j.contains("defaultStart"))
            def.defaultStart = j["defaultStart"].get<SDL_FPoint>();

        if (j.contains("defaultEnd"))
            def.defaultEnd = j["defaultEnd"].get<SDL_FPoint>();

        // ---- Config ----
        def.config = j.at("config").get<lightningStormConfig>();

        defs.emplace(def.id, std::move(def));
    }

    return true;
}

const lightningStormDef* lightningStormBank::get(const std::string& id) const
{
    auto it = defs.find(id);
    if (it == defs.end())
        return nullptr;

    return &it->second;
}