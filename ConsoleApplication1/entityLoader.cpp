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


	void loadEntityFromFactoryJson(const nlohmann::ordered_json& j, entity& e) {
		if (j.contains("name")) e.setName(j.at("name").get<std::string>());
		if (j.contains("entityId")) e.setEntityId(j.at("entityId").get<int>());
		if (j.contains("factoryId")) e.setFactoryId(j.at("factoryId").get<int>());
		if (j.contains("stats")) e.getStats() = j.at("stats").get<statsContainer>();

		if (j.contains("abilities")) {
			for (const auto& abName : j["abilities"]) {
				auto ability = abilityFactory::getInstance().create(abName.get<std::string>());
				if (ability) {
					e.getAbilities().addAbility(std::move(ability));
				}
			}
		}
	}

	void loadEntityFromSaveJson(const nlohmann::ordered_json& j, entity& e) {
		if (j.contains("name")) e.setName(j.at("name").get<std::string>());
		if (j.contains("entityId")) e.setEntityId(j.at("entityId").get<int>());
		if (j.contains("factoryId")) e.setFactoryId(j.at("factoryId").get<int>());
		if (j.contains("stats")) e.getStats() = j.at("stats").get<statsContainer>();

		if (j.contains("abilities")) {
			for (const auto& abJson : j["abilities"]) {
				if (!abJson.contains("name")) {
					logManager::logThis("Ability JSON missing 'name' field.");
					continue;
				}

				std::string name = abJson.at("name").get<std::string>();
				std::unique_ptr<ability> ab;

				if (name == "heal") {
					auto h = std::make_unique<heal>();
					h->from_Json(abJson);
					ab = std::move(h);
				}
				// else if (name == "fireball") { ... }

				if (ab) {
					e.getAbilities().addAbility(std::move(ab));
				}
			}
		}
	}
}