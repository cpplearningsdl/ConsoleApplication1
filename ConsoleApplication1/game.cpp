#include "game.h"
#include <iostream>
#include "entityIncludes.h"
#include "movementHandler.h"
#include "renderablesCacheHandler.h"

game::game() {
	// init map, entities, etc. 
	logManager::logThis("started first game");  
	addEntityToGame("Bone Thug", ENTITY);

	entity& test = getEntityById(0);
	test.getAnimationManager().loadAnimation("idle"); 
	test.getAnimationManager().setMovement(movementTypeEnum::idle, 0, 0, 0, 0);
	test.updateRenderInfo();
	test.setRender(true); 
	test.getAnimationManager().setHoldFor(45);
	
	test.setPos({ 150, 150 });
	entity* rawPtr = entities.back().get();
	addToRenderables(renderableEntitiesCache, rawPtr, view);

	logManager::logThis("Spilling Guts:");
	test.spill_guts();

	addEntityToGame("stone_brick_floor", TILE);
	entity& floorTest = getEntityById(1);
	floorTest.getAnimationManager().loadAnimation("idle");
	floorTest.getAnimationManager().setMovement(movementTypeEnum::idle, 0, 0, 0, 0);
	floorTest.updateRenderInfo();
	floorTest.setRender(true);
	floorTest.setPos({ 350, 350 });
	rawPtr = tiles.back().get();
	addToRenderables(renderableTilesCache, rawPtr, view);
	floorTest.spill_guts();

	view.moving = true;
	view.targetPos = { 150, 150 };
	view.speed = .3;
}

game::~game() {
	// cleanup
}

void game::update(inputManager& input) {
	for (auto& e : tiles) {
		//entity->update(); 
		e->getAnimationManager().step();
		handleMovement(*e);
		e->updateRenderInfo();
	}
	for (auto& e : entities) {
		//entity->update(); 
		e->getAnimationManager().step();
		handleMovement(*e);
		e->updateRenderInfo();
	} 
	updateView();
}
 
void game::addEntityToGame(std::string name, ENTITYTYPEENUM type) {
	if (type == TILE) {//floor tiles
		tiles.push_back(entityFactory::getInstance().create(name));
		tiles.back()->setEntityId(nextId++); 
	}
	else {//entities/characters
		entities.push_back(entityFactory::getInstance().create(name));
		entities.back()->setEntityId(nextId++); 
	} 
}

void game::removeEntityFromGame(int id) {
	auto entityEntity = std::remove_if(entities.begin(), entities.end(),
		[id](const std::unique_ptr<entity>& e) { return e->getId() == id; });
	entities.erase(entityEntity, entities.end());

	auto tileEntity = std::remove_if(tiles.begin(), tiles.end(),
		[id](const std::unique_ptr<entity>& e) { return e->getId() == id; });
	tiles.erase(tileEntity, tiles.end());

	// Remove from cache
	//auto pit = std::remove_if(renderableEntitiesCache.begin(), renderableEntitiesCache.end(),
	//	[id](entity* e) { return e->getId() == id; });
	//renderableEntitiesCache.erase(pit, renderableEntitiesCache.end());
	removeFromRenderables(renderableEntitiesCache, id);
	removeFromRenderables(renderableTilesCache, id);

}

entity& game::getEntityById(int id) {
	logManager::logThis("getting entity by id ", id);
	for (auto& e : entities) { 
		logManager::logThis("checking id ", e->getId());
		if (e && e->getId() == id) {
			return *e;  // return reference to the entity
		}
	}
	for (auto& e : tiles) {
		logManager::logThis("checking id ", e->getId());
		if (e && e->getId() == id) {
			return *e;  // return reference to the tile
		}
	}
	throw std::runtime_error("entity with id " + std::to_string(id) + " not found.");
}

void game::updateView() {
	if (view.moving) {
		logManager::logThis("Camera view moving");
		moveView(view);//this can return true(still moving) vs false (at dest)
		pruneRenderables(renderableEntitiesCache, view);
		pruneRenderables(renderableTilesCache, view);
	}
}