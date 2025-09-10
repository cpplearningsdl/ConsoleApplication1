#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "json.hpp"
#include "logManager.h"  
#include "abilityFileLoader.h"
#include "ability.h"
#include "heal.h"

class abilityFactory {
public:
	static abilityFactory& getInstance() {
		static abilityFactory instance;
		return instance;
	}
	 
	abilityFactory(const abilityFactory&) = delete;
	abilityFactory& operator=(const abilityFactory&) = delete;
	 
	void registerAbility(const std::string& name, std::unique_ptr<ability> prototype) {
		prototypes[name] = std::move(prototype);
	}
	 
	void loadDefaultAbilities() {
		std::string path = R"(C:\Users\Keary\source\repos\ConsoleApplication1-working\ConsoleApplication1\abilityFiles)";
		abilityFileLoader::loadAllAbilitiesFromDir(path); 
	};

	std::unique_ptr<ability> create(const std::string& name) const {
		auto it = prototypes.find(name);
		if (it != prototypes.end()) {
			return it->second->clone(); 
		}
		logManager::logThis("Unable to create ability by name: ", name);
		return nullptr; // not found
	}

private:
	abilityFactory() { 
	}

	std::unordered_map<std::string, std::unique_ptr<ability>> prototypes;
};
