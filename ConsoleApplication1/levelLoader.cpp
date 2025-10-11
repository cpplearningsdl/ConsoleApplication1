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
	g.resizeFloorMap(lvl.state.mapSize.getH() * lvl.state.mapSize.getW()); 
	logManager::logThis("Setting View pos.");
	g.getViewNonConst().viewPos = lvl.state.viewPos;
	logManager::logThis("Loading Entities");
	loadEntities(g, lvl);
	logManager::logThis("Loading Tiles");
	loadTiles(g, lvl);
	logManager::logThis("Setting currentLevelData");
	g.setLevelData(lvl);
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
	int index = 0;
	for (auto& id : lvl.state.entityIds) {
		g.addEntityToGame(id, ENTITY); 
		g.getEntities().back()->setPos(lvl.state.entityPositions[index]);
		g.addToRenderablesCache(g.getEntities().back().get(), ENTITY);
		index++;
	} 
} 
void loadTiles(game& g, levelData& lvl) {
	const int tileSize = 128; 
	int mapW = g.getView().mapSize.getW();
	int mapH = g.getView().mapSize.getH();

	float x = 0;
	float y = 0;

	for (auto& id : lvl.state.tileIds) {
		g.addEntityToGame(id, TILE);
		entity* e = g.getTiles().back().get(); 
		e->setPos({ x, y }); 
		x += tileSize;
		if (x >= mapW * tileSize) {
			x = 0;
			y += tileSize;
		} 
		g.addTileToFloorMap(e);
		g.addToRenderablesCache(e, TILE);
	}
}