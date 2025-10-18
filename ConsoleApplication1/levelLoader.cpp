#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "levelLoader.h" 
#include "game.h"
#include "logManager.h"
#include "json.hpp"

void loadLevel(game& g, int l) {
	logManager::logThis("Loading Level");
	levelData lvl = loadLevelFile(l);

	logManager::logThis("Resizing Floor Map");
	g.getEntityHandler().resizeFloorMap(lvl.state.mapSize.getH() * lvl.state.mapSize.getW()); 
	
	logManager::logThis("Setting currentLevelData");
	g.setLevelData(lvl); 
	
	logManager::logThis("Setting View pos.");
	g.getViewNonConst().viewPos = lvl.state.viewPos;
	
	logManager::logThis("Loading Entities");
	loadEntities(g, lvl);
	
	logManager::logThis("Loading Tiles");
	loadTiles(g, lvl);

	logManager::logThis("Finished loading level.");
}
levelData loadLevelFile(int levelNumber) {
	char* appData = nullptr;
	size_t len = 0;

	// Use _dupenv_s to get APPDATA safely
	errno_t err = _dupenv_s(&appData, &len, "APPDATA");
	if (err != 0 || appData == nullptr) {
		throw std::runtime_error("APPDATA environment variable not found.");
		logManager::logThis("APPDATA environment variable not found.");
	}

	std::filesystem::path basePath = appData;
	free(appData); // must free buffer allocated by _dupenv_s

	basePath /= "ConsoleApplication1";
	basePath /= "levels";

	std::filesystem::create_directories(basePath);

	std::filesystem::path filePath = basePath / (std::to_string(levelNumber) + ".json");

	logManager::logThis("Trying to open level file path: " + filePath.string());
	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open level file: " + filePath.string());

		logManager::logThis("Failed to open level file path: " + filePath.string());
	}

	nlohmann::ordered_json j;
	file >> j;
	file.close();

	levelData lvl;
	from_json(j, lvl);

	return lvl;
}

void loadEntities(game& g, levelData& lvl) {
	entityManager& entities = g.getEntityHandler();
	const viewPort view = g.getView();
	int index = 0;
	for (auto& id : lvl.state.entityIds) {
		entities.createEntity(id, ENTITY, view);
		entities.getEntities().back()->setPos(lvl.state.entityPositions[index]);
		g.getRenderCacheManager().addToRenderablesCache(entities.getEntities().back().get(), view);
		index++;
	} 
} 
void loadTiles(game& g, levelData& lvl) {
	entityManager& entities = g.getEntityHandler();
	const viewPort& view = g.getView();
	const int tileSize = 128; 
	int mapW = lvl.state.mapSize.getW();
	int mapH = lvl.state.mapSize.getH();
	 
	float x = 0;
	float y = 0;

	for (auto& id : lvl.state.tileIds) {
		entities.createEntity(id, TILE, view);
		entity* e = entities.getTiles().back().get(); 
		e->setPos({ x, y }); 
		x += tileSize;
		if (x >= mapW * tileSize) {
			x = 0;
			y += tileSize;
		} 
		entities.addTileToFloorMap(e, view);
		g.getRenderCacheManager().addToRenderablesCache(e, view);
	}
}