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
	loadALevel(1);
	startRotation(view, { 64, 64 }, 1,128, .033, false, .3);
}

game::~game() {
	// cleanup
}

void game::update(inputManager& input) {
	updateCount++;

	updateEntities(tiles);
	updateEntities(entities);
 
	updateView(); 
}

void game::updateEntities(std::vector<std::unique_ptr<entity>>& entitiesVector) {
	for (auto& e : entitiesVector) {
		e->getAnimationManager().step();
		handleMovement(*e);
		e->updateRenderInfo();
	}
}

void game::loadALevel(int l) {
	loadLevel(*this, l);
}
void game::addTileToFloorMap(entity* e) {
	position pos = toGridCoords(e->getPos(), this->view);
	int index = gridToIndex(pos, this->view);
	if (index >= 0 && index < static_cast<int>(floorMap.size())) {
		floorMap[index] = e;
	}
}

void game::addEntityToGame(int factoryId, ENTITYTYPEENUM type) {
	auto& factory = entityFactory::getInstance();
	entity* e = createEntity(factoryId, type, factory);
	//if (type == TILE) {	addTileToFloorMap(e);}
	//addToRenderablesCache(e, type); POS NOT SET BY LOADER BEFORE THIS
	//logManager::logThis("Added entity to game: ", e->getName());
}

void game::addEntityToGame(int factoryId) {
	auto& factory = entityFactory::getInstance();
	ENTITYTYPEENUM type = factory.getType(factoryId);
	entity* e = createEntity(factoryId, type, factory);
	if (type == TILE) {	addTileToFloorMap(e); } 
	//addToRenderablesCache(e, type); POS NOT SET BY LOADER BEFORE THIS
	logManager::logThis("Added entity to game: ", e->getName());
}

entity* game::createEntity(int factoryId, ENTITYTYPEENUM type, entityFactory& f) {
	if (type == TILE) {
		tiles.push_back(f.create(factoryId));
		entity* e = tiles.back().get();
		e->setEntityId(nextId++);
		return e;
	}
	if (type == ENTITY) {
		entities.push_back(f.create(factoryId));
		entity* e = entities.back().get();
		e->setEntityId(nextId++);
		return e;
	}
	return NULL;
}

void game::addEntityToGameFromJson(const std::string& jsonFilePath) {
	// Load JSON
	std::ifstream file(jsonFilePath);
	if (!file.is_open()) return;

	nlohmann::ordered_json j;
	file >> j;
	 
	ENTITYTYPEENUM type = ENTITY;
	if (j.contains("type")) {
		type = entityTypeFromString(j.at("type").get<std::string>());
	}

	entity* rawPtr = nullptr;
	 
	if (type == TILE) {
		tiles.push_back(std::make_unique<entity>());
		rawPtr = tiles.back().get();
	}
	else {
		entities.push_back(std::make_unique<entity>());
		rawPtr = entities.back().get();
	}
	 
	rawPtr->from_Json(j); 
	rawPtr->setEntityId(nextId++);
	 
	if (type == TILE) {
		addTileToFloorMap(rawPtr);
	}

	addToRenderablesCache(rawPtr, type);
}

 
void game::removeEntityFromGame(int id) {
	auto removeFromContainer = [&](auto& container, ENTITYTYPEENUM type) {
		auto it = std::find_if(container.begin(), container.end(), [id](const std::unique_ptr<entity>& e) { return e->getId() == id; });

		if (it == container.end()) return false;

		entity* e = it->get();
		removeFromRenderablesCache(e, type);
		if (type == TILE) {
			position pos = toGridCoords(e->getPos(), this->view);
			int index = gridToIndex(pos, this->view);
			if (index >= 0 && index < static_cast<int>(floorMap.size()) && floorMap[index] == e)
				floorMap[index] = nullptr;
		}
		container.erase(it);
		logManager::logThis("removed entity from game: ", e->getName());
		return true;
	};

	if (removeFromContainer(entities, ENTITY)) return;
	removeFromContainer(tiles, TILE);
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
		moveView(view); 

		generateRenderablesCache(entities, renderableEntitiesCache, this->view);
		generateTileRenderablesCache(floorMap, renderableTilesCache, this->view);
	}
	if (view.rotating) {
		updateRotation(this->view);
	}
}

void game::addToRenderablesCache(entity* e, ENTITYTYPEENUM t) {
	// Add to render cache if in view
	if (t == TILE) {
		if (testInView(this->view, e->getPos(), { e->getAnimationManager().getHeight(),  e->getAnimationManager().getWidth() })) {
			renderableTilesCache.push_back(e);
			//logManager::logThis("Added entity to rendercache: ", e->getName());
		}
	}
	else {
		if (testInView(this->view, e->getPos(), { e->getAnimationManager().getHeight(),  e->getAnimationManager().getWidth() })) {
			renderableEntitiesCache.push_back(e);
			//logManager::logThis("Added entity to rendercache: ", e->getName());
		}
	}
};
void game::removeFromRenderablesCache(entity* e, ENTITYTYPEENUM t) {
	if (!e) return;

	int id = e->getId();

	switch (t) {
	case ENTITY:
		removeFromRenderables(renderableEntitiesCache, id);
		break;

	case TILE:
		removeFromRenderables(renderableTilesCache, id);
		break;

	default:
		// If unknown type, try both
		removeFromRenderables(renderableEntitiesCache, id);
		removeFromRenderables(renderableTilesCache, id);
		break;
	}
}

void game::updateRenderablesCache(ENTITYTYPEENUM t) { };
void game::fullBuildRenderablesCache(ENTITYTYPEENUM t) { };
void game::buildAllRenderablesCache() { };