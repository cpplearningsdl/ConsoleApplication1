#pragma once
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include "json.hpp"
#include "logManager.h"
#include "rainStormBank.h"
#include "rainStormDef.h"
#include "fileSystemHelper.h"

using json = nlohmann::ordered_json;


rainStormBank::rainStormBank() {
    loadFromDirectory(getRainStormDefaultsPath());
};

rainStormBank::~rainStormBank() {
    defs.clear();
};

const rainStormDef rainStormBank::get(const std::string& id) const
{
    auto it = defs.find(id);

    return it->second;
}

bool rainStormBank::loadFromDirectory(const std::filesystem::path& path) {
    logManager::logThis("Attempting to load rainStormBank");
    if (!fs::exists(path) || !fs::is_directory(path)) {
        logManager::logThis("Failed to load rainStormBank: Path or Directory is missing; ", path.generic_string());
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

        rainStormDef def;

        def.id = j.at("id").get<std::string>();


        // ---- Config ----
        logManager::logThis("Trying to load a default rain storm to bank..."); 
        try {
            def.config = j.at("config").get<rainStormConfig>();
        }
        catch (const std::exception& e) {
            std::cout << "Parse error: " << e.what() << "\n";
            std::cout << j.dump(4) << "\n";
            throw;
        }
        defs.emplace(def.id, std::move(def));
    }

    return true;
}

