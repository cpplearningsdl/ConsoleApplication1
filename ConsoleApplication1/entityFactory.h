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

	std::unique_ptr<entity> create(const std::string& name) {
		auto it = prototypes.find(name);
		if (it != prototypes.end()) {
			return std::make_unique<entity>(*it->second); // copy constructor
		}
		return nullptr;
	}
	void loadDefaultEntities() { entityLoader::loadAllDefaultEntitiesFromDir("C:\\Users\\Keary\\source\\repos\\ConsoleApplication1-working\\ConsoleApplication1\\defaultEntities"); };
private:
	entityFactory() = default;
	std::unordered_map<std::string, std::unique_ptr<entity>> prototypes;
};
 