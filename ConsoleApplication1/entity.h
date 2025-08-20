#pragma once
#include <string> 

#include "abilities.h"
#include "stats.h"


class entity {
public:
	entity(int id);

  
	void update();

	stats& getStats();
	const stats& getStats() const;
	
	abilities& getAbilities();
	const abilities& getAbilities() const;

private:
	int entityId;
	std::string name;

	abilities abilities;
	stats stats;
};
