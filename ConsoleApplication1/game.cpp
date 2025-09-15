#include "game.h"
#include <iostream>

game::game() {
	// init map, entities, etc. 
	logManager::logThis("started first game");
	entities.push_back(entityFactory::getInstance().create("bone_thug"));
	entities.push_back(entityFactory::getInstance().create("black_piece"));

	entity& test = getEntityById(2);
	test.getAnimationManager().loadAnimation("idle");
}

game::~game() {
	// cleanup
}

void game::update() { 

 
}
std::vector<entity*> game::getRenderables()
{
	std::vector<entity*> list;
	list.reserve(entities.size());

	for (auto& e : getEntities()) {
		list.push_back(e.get()); // expose raw pointer
	}

	// sort however you like
	std::sort(list.begin(), list.end(),
		[](entity* a, entity* b) {
		return a->getPos().getY() < b->getPos().getY();
	});

	return list;
}

entity& game::getEntityById(int id) {
	for (auto& e : entities) {
		if (e && e->getFactoryId() == id) {
			return *e;  // return reference to the entity
		}
	}
	throw std::runtime_error("entity with id " + std::to_string(id) + " not found.");
}