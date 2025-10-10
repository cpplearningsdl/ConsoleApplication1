#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "levelLoader.h" 
#include "game.h"
#include "logManager.h"
#include "json.hpp"

void loadLevel(game& g) {
	levelData lvl = loadLevelFile(1);
	//g.setLevelData(std::move(lvl)); 
	g.setLevelData(loadLevelFile(1));
	g.getViewNonConst().viewPos = lvl.state.viewPos;

}
levelData loadLevelFile(int levelNumber) {
	char* appData = nullptr;
	size_t len = 0;

	// Use _dupenv_s to get APPDATA safely
	errno_t err = _dupenv_s(&appData, &len, "APPDATA");
	if (err != 0 || appData == nullptr) {
		throw std::runtime_error("APPDATA environment variable not found.");
	}

	std::filesystem::path basePath = appData;
	free(appData); // must free buffer allocated by _dupenv_s

	basePath /= "ConsoleApplication1";
	basePath /= "levels";

	std::filesystem::create_directories(basePath);

	std::filesystem::path filePath = basePath / (std::to_string(levelNumber) + ".json");

	std::ifstream file(filePath);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open level file: " + filePath.string());
	}

	nlohmann::ordered_json j;
	file >> j;
	file.close();

	levelData lvl;
	from_json(j, lvl);

	return lvl;
}

void loadEntities(game& g) {


}