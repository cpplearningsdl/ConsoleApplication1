#include "entityLoader.h"
#include <filesystem>
#include <fstream>
#include "entityFactory.h"
#include "entity.h"
#include "logManager.h"
#include "json.hpp"

namespace fs = std::filesystem;

namespace entityLoader {

	void loadAllDefaultEntitiesFromDir(const std::string& dirPath) {
		logManager::logThis("Attempting to load entities from path: " + dirPath);

		// Check if directory exists
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
				std::string filename = entry.path().stem().string(); // name without extension

				std::ifstream file(entry.path());
				if (!file.is_open()) {
					logManager::logThis("Could not open entity file: " + entry.path().string());
					continue;
				}

				nlohmann::ordered_json j;
				try {
					file >> j;
				}
				catch (const std::exception& e) {
					logManager::logThis("Error parsing entity JSON (" + entry.path().string() + "): " + e.what());
					continue;
				}

				// Construct a prototype entity
				auto prototype = std::make_unique<entity>();
				try {
					prototype->from_Json(j);
				}
				catch (const std::exception& e) {
					logManager::logThis("Error loading entity data from " + filename + ": " + e.what());
					continue;
				}

				// Register with factory
				entityFactory::getInstance().registerEntity(filename, std::move(prototype));
				logManager::logThis("Registered entity: " + filename + "\n"); 
			}
		}

		if (!anyJsonFound) {
			logManager::logThis("No .json entity files found in: " + dirPath);
		}
	}

	//ADD ENTITY LOADING FROM SAVED JSON NOT JUST FACTORY
}