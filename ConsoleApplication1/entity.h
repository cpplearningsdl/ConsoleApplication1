#pragma once
#include <string>  
#include "abilities.h"
#include "statsContainer.h"
#include "abilityFactory.h"
#include "json.hpp"


class entity {
public:
	entity();
	entity(const entity&) = default;
	entity& operator=(const entity&) = default;
  
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
	static nlohmann::json to_Json(const entity& e);
	void from_Json(const nlohmann::json&j);

private:
	int entityId;
	int factoryId;

	std::string name;
	statsContainer stats;
	abilities abilities; 
};
 