#pragma once
#include <string>  
#include "abilities.h"
#include "statsContainer.h"
#include "C:\Users\Keary\source\repos\ConsoleApplication1\ConsoleApplication1\include\json.hpp"


class entity {
public:
	entity(int factoryId);

  
	void update(); 

	std::string getName() const { return name; };
	void setName(std::string newName) {	name = newName;	};
	void setEntityId(int newId) { entityId = newId; };
	void setFactoryId(int newId) { factoryId = newId; };
	int getId() const { return entityId; }
	int getFactoryId() const { return factoryId; } 
	const statsContainer& getStats() const { return stats; }
	statsContainer& getStats() { return stats; }

	abilities& getAbilities();
	const abilities& getAbilities() const;
	static nlohmann::json entityToJson(const entity& e);

private:
	int entityId;
	int factoryId;

	std::string name;
	statsContainer stats;
	abilities abilities; 
};
 