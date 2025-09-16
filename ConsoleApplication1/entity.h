#pragma once
#include <string>  
#include "animationManager.h"
#include "abilities.h"
#include "statsContainer.h"
#include "position.h"
#include "abilityFactory.h"
#include "json.hpp"


class entity {
public:
	entity();
	~entity() = default;

	// Deep copy constructor
	entity(const entity& other);

	// Deep copy assignment
	entity& operator=(const entity& other);

	// Move semantics
	entity(entity&&) noexcept = default;
	entity& operator=(entity&&) noexcept = default;

	void update(); 

	std::string getName() const { return name; };
	void setName(std::string newName) {	name = newName;	};
	void setEntityId(int newId) { entityId = newId; };
	void setFactoryId(int newId) { factoryId = newId; };
	int getId() const { return entityId; }
	int getFactoryId() const { return factoryId; } 
	const statsContainer& getStats() const { return stats; }
	statsContainer& getStats() { return stats; }
	const position& getPos() const { return pos; }
	position& getPos() { return pos; }

	abilities& getAbilities();
	const abilities& getAbilities() const; 
	animationManager& getAnimationManager() { return animationHandler; }
	static nlohmann::ordered_json to_Json(const entity& e);
	void from_Json(const nlohmann::ordered_json& j);
	void spill_guts();
private:
	int entityId;
	int factoryId;
	position pos;

	std::string name;
	statsContainer stats;
	abilities abilities; 
	
	animationManager animationHandler;
};
 