#include "game.h"
#include <iostream>
#include <fstream> 
#include <memory> 
#include "levelLoader.h"
#include "entityIncludes.h"
#include "entityTypeEnum.h"
#include "movementHandler.h"
#include "renderablesCacheHandler.h"

game::game() {
	// init map, entities, etc. 
	logManager::logThis("started first game");  
	addEntityToGame(0, ENTITY); 
	entity& test = getEntityById(0);  

	logManager::logThis("Spilling Guts:");
	test.spill_guts("SpillGutsTest");

	addEntityToGame(2, TILE);
	entity& floorTest = getEntityById(1); 
	floorTest.spill_guts();

	view.moving = true;
	view.targetPos = { 150, 150 };
	view.speed = 0.4;
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
 
void game::loadLevel(int l) {

}
void game::addEntityToGame(int factoryId, ENTITYTYPEENUM type) {
	if (type == TILE) { // floor tiles
		tiles.push_back(entityFactory::getInstance().create(factoryId));
		entity* e = tiles.back().get();
		e->setEntityId(nextId++);

		// Check if in view, add to tile render cache
		if (testInView(view, e->getPos(),
			{ e->getAnimationManager().getHeight(), e->getAnimationManager().getWidth() })) {
			renderableTilesCache.push_back(e);
		}
	}
	else { // entities/characters
		entities.push_back(entityFactory::getInstance().create(factoryId));
		entity* e = entities.back().get();
		e->setEntityId(nextId++);

		// Check if in view, add to entity render cache
		if (testInView(view, e->getPos(),
			{ e->getAnimationManager().getHeight(), e->getAnimationManager().getWidth() })) {
			renderableEntitiesCache.push_back(e);
		}
	}
}

void game::addEntityToGame(int factoryId) {
	auto& factory = entityFactory::getInstance();
	ENTITYTYPEENUM type = factory.getType(factoryId);

	if (type == TILE) {
		// Create tile
		tiles.push_back(factory.create(factoryId));
		entity* e = tiles.back().get();
		e->setEntityId(nextId++);

		position pos = toGridCoords(e->getPos(), this->view);
		floorMap[gridToIndex(pos, this->view)] = e;

		// Add to render cache if in view
		if (testInView(this->view, e->getPos(),	{ e->getAnimationManager().getHeight(),  e->getAnimationManager().getWidth() })) {
			renderableTilesCache.push_back(e);
		}
				
	}
	else {
		// Create entity/character
		entities.push_back(factory.create(factoryId));
		entity* e = entities.back().get();
		e->setEntityId(nextId++);

		// Add to render cache if in view
		if (testInView(this->view, e->getPos(),	{ e->getAnimationManager().getHeight(), e->getAnimationManager().getWidth() })) {
			renderableEntitiesCache.push_back(e);
		}
	}
}

void game::addEntityToGameFromJson(const std::string& jsonFilePath) {
	// Load JSON
	std::ifstream file(jsonFilePath);
	if (!file.is_open()) return;
	nlohmann::json j;
	file >> j;

	// Determine type from JSON (default ENTITY)
	ENTITYTYPEENUM type = ENTITY;
	if (j.contains("type")) {
		type = entityTypeFromString(j.at("type").get<std::string>());
	}

	// Temporary pointer for render cache check
	entity* rawPtr = nullptr;

	if (type == TILE) {
		tiles.push_back(std::make_unique<entity>());
		rawPtr = tiles.back().get();
	}
	else {
		entities.push_back(std::make_unique<entity>());
		rawPtr = entities.back().get();
	}

	// Initialize from JSON
	rawPtr->from_Json(j);

	// Set unique ID
	rawPtr->setEntityId(nextId++);

	// Add to render cache if in view
	if (testInView(this->view, rawPtr->getPos(), { rawPtr->getAnimationManager().getHeight(), rawPtr->getAnimationManager().getWidth() })) {
		if (type == TILE) renderableTilesCache.push_back(rawPtr);
		else renderableEntitiesCache.push_back(rawPtr);
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

//RUN TIME ID NOT FACTORY
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
		moveView(view);//this can return true(still moving) vs false (at dest)
		pruneRenderables(renderableEntitiesCache, view);
		pruneRenderables(renderableTilesCache, view);
	}
}

void game::addToRenderablesCache(entity* e, ENTITYTYPEENUM t) {
	// Add to render cache if in view
	if (t == TILE) {
		if (testInView(this->view, e->getPos(), { e->getAnimationManager().getHeight(),  e->getAnimationManager().getWidth() })) {
			renderableTilesCache.push_back(e);
		}
	}
	else {
		if (testInView(this->view, e->getPos(), { e->getAnimationManager().getHeight(),  e->getAnimationManager().getWidth() })) {
			renderableEntitiesCache.push_back(e);
		}
	}
};
void game::removeFromRenderablesCache(entity* e, ENTITYTYPEENUM t) { };
void game::updateRenderablesCache(ENTITYTYPEENUM t) { };
void game::fullBuildRenderablesCache(ENTITYTYPEENUM t) { };
void game::buildAllRenderablesCache() { };