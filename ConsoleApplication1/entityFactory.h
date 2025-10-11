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

	void registerEntity(int id, std::unique_ptr<entity> prototype) {
		prototypes[id] = std::move(prototype);
	}

	ENTITYTYPEENUM getType(int id) {
		auto it = prototypes.find(id);
		if (it != prototypes.end() && it->second) {
			return it->second->getType();  
		}
		return MISSING; // default fallback if not found
	}

	std::unique_ptr<entity> create(int id) {
		//logManager::logThis("Trying to add entity to game: id ", id);
		auto it = prototypes.find(id);
		if (it != prototypes.end()) {
			//logManager::logThis("Added entity to game: id", id);
			return std::make_unique<entity>(*it->second); // copy constructor

		}
		logManager::logThis("Couldn't find entity: id ", id);
		return nullptr;
	}


	void loadDefaultEntities() { entityLoader::loadAllDefaultEntitiesFromDir("C:\\Users\\Keary\\source\\repos\\ConsoleApplication1-working\\ConsoleApplication1\\defaultEntities"); };
private:
	entityFactory() = default;
	//std::unordered_map<std::string, std::unique_ptr<entity>> prototypes;
	std::unordered_map<int, std::unique_ptr<entity>> prototypes;
};
 