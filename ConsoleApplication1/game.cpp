#include "game.h"
#include <iostream>
#include "movementHandler.h"

game::game() {
	// init map, entities, etc. 
	logManager::logThis("started first game");  
	addEntityToGame("black_piece");

	entity& test = getEntityById(0);
	test.getAnimationManager().loadAnimation("walk");//FIGURE OUT HOW TO USE WALK ANIMATION
	test.getAnimationManager().setMovement(movementTypeEnum::north, 0, 0, 250, 40);
	test.updateRenderInfo();
	test.setRender(true); 
	test.getAnimationManager().setHoldFor(5);
	logManager::logThis("Spilling Guts:");
	test.spill_guts();
}

game::~game() {
	// cleanup
}

void game::update(inputManager& input) {
	for (auto& e : entities) {
		//entity->update(); 
		e->getAnimationManager().step();
		handleMovement(*e);
		e->updateRenderInfo();
	} 
}
 
void game::addEntityToGame(std::string name) {
	//tmp
	name = "black_piece";
	entities.push_back(entityFactory::getInstance().create(name));
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