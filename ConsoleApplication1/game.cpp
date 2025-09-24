#include "game.h"
#include <iostream>

game::game() {
	// init map, entities, etc. 
	logManager::logThis("started first game");  
	addEntityToGame("black_piece");

	entity& test = getEntityById(0);
	test.getAnimationManager().loadAnimation("idle");
	test.updateRenderInfo();
	test.setRender(true); 
	test.getAnimationManager().setHoldFor(10);
	logManager::logThis("Spilling Guts:");
	test.spill_guts();
}

game::~game() {
	// cleanup
}

void game::update() { 
	for (auto& entity : entities) {
		entity->update();
	}
 
}
 
void game::addEntityToGame(std::string name) {
	entities.push_back(entityFactory::getInstance().create("black_piece"));
	entities.back()->setEntityId(nextId++);

	entity* rawPtr = entities.back().get(); 
	renderablesCache.push_back(rawPtr);
}

void game::removeEntityFromGame(int id) {
	auto it = std::remove_if(entities.begin(), entities.end(),
		[id](const std::unique_ptr<entity>& e) { return e->getId() == id; });
	entities.erase(it, entities.end());

	// Remove from cache
	auto pit = std::remove_if(renderablesCache.begin(), renderablesCache.end(),
		[id](entity* e) { return e->getId() == id; });
	renderablesCache.erase(pit, renderablesCache.end());
}

entity& game::getEntityById(int id) {
	logManager::logThis("getting entity by id ", id);
	for (auto& e : entities) { 
		logManager::logThis("checking id ", e->getId());
		if (e && e->getId() == id) {
			return *e;  // return reference to the entity
		}
	}
	throw std::runtime_error("entity with id " + std::to_string(id) + " not found.");
}