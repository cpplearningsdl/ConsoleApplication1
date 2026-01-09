#pragma once
#include <vector>
#include <string> 
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include "json.hpp" 
#include "logManager.h"
#include "fireStormBank.h"
#include "fileSystemHelper.h"

using json = nlohmann::ordered_json;


fireStormBank::fireStormBank() {
    loadFromDirectory(getStormDefaultsPath());
}
fireStormBank::~fireStormBank() {
    defs.clear();
}
bool fireStormBank::loadFromDirectory(const std::filesystem::path& path) {
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

        fireStormDef def;

        def.id = j.at("id").get<std::string>();


        // ---- Config ----
          def.config = j.at("config").get<fireStormConfig>();

        defs.emplace(def.id, std::move(def));
    }

    return true;
}

const fireStormDef fireStormBank::get(const std::string& id) const
{
    auto it = defs.find(id); 

    return it->second;
}