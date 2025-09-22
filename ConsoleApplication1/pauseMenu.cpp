#pragma once
#include "pauseMenu.h"
#include "json.hpp"
#include <fstream>
#include <stdexcept>

pauseMenu::pauseMenu() {
	load();


} 

void pauseMenu::load() {
	loadJson();
	loadButtons();
}

//	buttonObj(position pos, position sz, std::function<void()> cb, std::string newName, std::string animationName, bool visible )
void pauseMenu::loadButtons() {
	buttons.emplace_back(
		position{ 100, 100 }, position{ 200, 50 },
		[&]() {  hide(); },
		"Resume",
		"idle",
		true
	); 
	buttons.emplace_back(
		position{ 100, 200 }, position{ 200, 50 },
		[&]() {},
		"Save",
		"idle",
		true
	);

	buttons.emplace_back(
		position{ 100, 300 }, position{ 200, 50 },
		[&]() {},
		"Quit",
		"idle",
		true
	);
}

void pauseMenu::loadJson( ) {
	std::string fileName = "C:\\Users\\Keary\\source\\repos\\ConsoleApplication1-working\\ConsoleApplication1\\menuJsons\\pause_menu.json";
	std::ifstream file(fileName);
	if (!file.is_open()) {
		logManager::logThis("Couldn't open pause menu .json");
		throw std::runtime_error("Failed to open pauseMenu JSON: " + fileName);
	}
	nlohmann::ordered_json j;
	file >> j;
	from_json(j, *this);
}

void pauseMenu::update() {
	animationHandler.step();
	updateEntityRenderInfo(renderInfo, animationHandler.getTextureKey(), pos, render);
	for (auto& btn : buttons) {
		btn.update();
	}
}