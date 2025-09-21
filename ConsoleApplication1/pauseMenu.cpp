#pragma once
#include "pauseMenu.h"
#include "json.hpp"
#include <fstream>
#include <stdexcept>

pauseMenu::pauseMenu() {
	std::string fileName = "C:\\Users\\Keary\\source\\repos\\ConsoleApplication1-working\\ConsoleApplication1\\menuJsons\\pause_menu.json"; 
	std::ifstream file(fileName);
	if (!file.is_open()) {
		logManager::logThis("Couldn't open pause menu .json");
		throw std::runtime_error("Failed to open pauseMenu JSON: " + fileName);
	} 
	nlohmann::ordered_json j;
	file >> j; 
	from_json(j, *this);

	buttons.emplace_back(
		Vec2{ 100, 100 }, Vec2{ 200, 50 },
		[&]() {  hide(); },
		"Resume"
	);

	buttons.emplace_back(
		Vec2{ 100, 200 }, Vec2{ 200, 50 },
		[&]() {},
		"Save"
	);

	buttons.emplace_back(
		Vec2{ 100, 300 }, Vec2{ 200, 50 },
		[&]() {},
		"Quit"
	);
}

void pauseMenu::update() {
	animationHandler.step();
	updateEntityRenderInfo(renderInfo, animationHandler.getTextureKey(), pos, render);
}