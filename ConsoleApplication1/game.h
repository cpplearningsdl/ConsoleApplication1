#pragma once
#include <vector> 
#include "entity.h"

class game {
public:
	game();
	~game();

	void update(); 

private:
	std::vector<std::unique_ptr<entity>> entities;
	//std::vector<std::unique_ptr<tile>> tiles;

}; 