#pragma once
#include <fstream> 
#include "entityManager.h"
#include "view.h"

entityManager::entityManager() {

}
entityManager::~entityManager(){
}

entity* entityManager::createEntity(int factoryId, ENTITYTYPEENUM type, const viewPort& v) {
	entityFactory& f = entityFactory::getInstance();
	if (type == TILE) {
		tiles.push_back(f.create(factoryId));
		entity* e = tiles.back().get();
		addTileToFloorMap(e, v);
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

void entityManager::addTileToFloorMap(entity* e, const viewPort& v) {
	position pos = toGridCoords(e->getPos(), v);
	int index = gridToIndex(pos, v);
	if (index >= 0 && index < static_cast<int>(floorMap.size())) {
		floorMap[index] = e;
	}
}
 
 
void entityManager::addEntityFromJson(const std::string& jsonFilePath, const viewPort& v) {
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
		addTileToFloorMap(rawPtr, v);
	} 
}

void entityManager::removeEntityFromGame(int id, viewPort& v) {
	// Try removing from entities
	auto itEntity = std::find_if(entities.begin(), entities.end(),
		[id](const std::unique_ptr<entity>& e) { return e->getId() == id; });
	if (itEntity != entities.end()) {
		logManager::logThis("removed entity from game: ", (*itEntity)->getName());
		entities.erase(itEntity);
		return;
	}

	// Try removing from tiles
	auto itTile = std::find_if(tiles.begin(), tiles.end(),
		[id](const std::unique_ptr<entity>& e) { return e->getId() == id; });
	if (itTile != tiles.end()) {
		entity* e = itTile->get();

		// Update floorMap
		position pos = toGridCoords(e->getPos(), v);
		int index = gridToIndex(pos, v);
		if (index >= 0 && index < static_cast<int>(floorMap.size()) && floorMap[index] == e) {
			floorMap[index] = nullptr;
		}

		logManager::logThis("removed tile from game: ", e->getName());
		tiles.erase(itTile);
	}
}

//RUN TIME ID NOT FACTORY
entity& entityManager::getEntityById(int id) {
	logManager::logThis("getting entity by id ", id);
	for (auto& e : entities) { 
		if (e && e->getId() == id) {
			return *e;  // return reference to the entity
		}
	}
	for (auto& e : tiles) { 
		if (e && e->getId() == id) {
			return *e;  // return reference to the tile
		}
	}
	throw std::runtime_error("entity with id " + std::to_string(id) + " not found.");
}
