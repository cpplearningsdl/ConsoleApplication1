#pragma once
#include "entity.h"
#include "json.hpp"
 
namespace entityLoader{

	void loadEntityFromFactoryJson(const json& j, entity& e);
 
	void loadEntityFromSaveJson(const json& j, entity& e);

	void loadAllDefaultEntitiesFromDir(const std::string& dirPath);
}