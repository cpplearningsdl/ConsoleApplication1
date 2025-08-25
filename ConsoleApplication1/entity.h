#pragma once
#include <string>  
#include "abilities.h"
#include "stats.h"


class entity {
public:
	entity(int id);

  
	void update(); 

	abilities& getAbilities();
	const abilities& getAbilities() const;

private:
	int entityId;
	std::string name;
	stats stats;
	abilities abilities; 
};
