#pragma once
#include <vector> 
#include "entityIncludes.h"

class game {
public:
	game();
	~game();

	void update(); 
	entity&  getEntityById(int id);
	std::vector<std::unique_ptr<entity>>& getEntities() { return entities; }
	std::vector<entity*> getRenderables();

private:
	std::vector<std::unique_ptr<entity>> entities;
	//std::vector<std::unique_ptr<tile>> tiles;

}; 