#pragma once
#include <string>
#include "entity.h" 

namespace entityLoader {
	void loadAllDefaultEntitiesFromDir(const std::string& dirPath);
}

class entityFactory {

public:

	static entityFactory& getInstance() {
		static entityFactory instance;
		return instance;
	}

	void registerEntity(const std::string& name, std::unique_ptr<entity> prototype) {
		prototypes[name] = std::move(prototype);
	}
	ENTITYTYPEENUM getType(const std::string& name) {
		auto it = prototypes.find(name);
		if (it != prototypes.end() && it->second) {
			return it->second->getType();  
		}
		return MISSING; // default fallback if not found
	}
	std::unique_ptr<entity> create(const std::string& name) {
		logManager::logThis("Trying to add entity to game: ", name);
		auto it = prototypes.find(name);
		if (it != prototypes.end()) {
			logManager::logThis("Added entity to game: ", name);
			return std::make_unique<entity>(*it->second); // copy constructor

		}
		logManager::logThis("Couldn't find entity: ", name);
		return nullptr;
	}
	void loadDefaultEntities() { entityLoader::loadAllDefaultEntitiesFromDir("C:\\Users\\Keary\\source\\repos\\ConsoleApplication1-working\\ConsoleApplication1\\defaultEntities"); };
private:
	entityFactory() = default;
	std::unordered_map<std::string, std::unique_ptr<entity>> prototypes;
};
 