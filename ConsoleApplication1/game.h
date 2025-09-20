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
	const std::vector<entity*>& getRenderables() const { return renderablesCache; }

	void addEntityToGame(std::string name);
	void removeEntityFromGame(int id);

private:
	int nextId = 0;
	std::vector<std::unique_ptr<entity>> entities;
	std::vector<entity*> renderablesCache;//IMPLEMENT THIS
	std::vector<std::unique_ptr<entity>> tiles;

}; 