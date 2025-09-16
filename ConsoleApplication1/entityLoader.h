#pragma once
#include "entity.h"
#include "json.hpp"
 
namespace entityLoader{

	//void loadEntityFromFactoryJson(const nlohmann::ordered_json& j, entity& e);
 //
	//void loadEntityFromSaveJson(const nlohmann::ordered_json& j, entity& e);

	void loadAllDefaultEntitiesFromDir(const std::string& dirPath);
}