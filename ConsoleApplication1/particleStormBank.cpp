#pragma once
#include <filesystem>
#include <fstream>
#include "logManager.h"
#include "particleBank.h"
#include "particleStormDef.h"
#include "fileSystemHelper.h"
#include "json.hpp"

using json = nlohmann::ordered_json;


particleStormBank::particleStormBank() {
	loadFromDirectory(getParticleStormDefaultsPath());
};

particleStormBank::~particleStormBank() {
	defs.clear();
};

const particleStormDef particleStormBank::get(const std::string& id) const
{
    auto it = defs.find(id);

    return it->second;
}

bool particleStormBank::loadFromDirectory(const std::filesystem::path& path) {
    logManager::logThis("Attempting to load particleBank");
    if (!fs::exists(path) || !fs::is_directory(path)) {
        logManager::logThis("Failed to load particleStormBank: Path or Directory is missing; ", path.generic_string());
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

        particleStormDef def;

        def.id = j.at("id").get<std::string>();


        // ---- Config ----
        logManager::logThis("Trying to load a default particle storm to bank...");
       // def.config = j.at("config").get<particleStormConfig>();
        try {
            def.config = j.at("config").get<particleStormConfig>();
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
