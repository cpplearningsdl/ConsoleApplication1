#include "abilityFileLoader.h"
#include <filesystem>
#include <fstream>
#include "json.hpp"
#include "logManager.h"
#include "abilityFactory.h"
#include "ability.h"
#include "heal.h"

namespace fs = std::filesystem;

namespace abilityFileLoader { 
	void loadAllAbilitiesFromDir(const std::string& dirPath) {
		logManager::logThis("Attempting to load abilities from path: " + dirPath);
		 
		if (!fs::exists(dirPath)) {
			logManager::logThis("Directory does not exist: " + dirPath);
			return;
		}
		if (!fs::is_directory(dirPath)) {
			logManager::logThis("Path is not a directory: " + dirPath);
			return;
		}

		bool anyJsonFound = false;

		for (const auto& entry : fs::directory_iterator(dirPath)) {
			if (entry.is_regular_file() && entry.path().extension() == ".json") {
				anyJsonFound = true;
				std::string filename = entry.path().stem().string();

				std::ifstream file(entry.path());
				if (!file.is_open()) {
					logManager::logThis("Could not open ability file: " + entry.path().string());
					continue;
				}

				nlohmann::json j;
				try {
					file >> j;
				}
				catch (const std::exception& e) {
					logManager::logThis("JSON parse error in " + entry.path().string() + ": " + e.what());
					continue;
				}
				 
				if (filename == "heal") {
					heal h;
					h.from_Json(j);
					abilityFactory::getInstance().registerAbility(
						h.getName(), std::make_unique<heal>(h));
					logManager::logThis("Registered Ability Heal");
				}
				// else if (filename == "fireball") { ... }
				else {
					logManager::logThis("Unknown ability json: " + filename);
				}
			}
		}

		if (!anyJsonFound) {
			logManager::logThis("No .json ability files found in: " + dirPath);
		}
	}

}
