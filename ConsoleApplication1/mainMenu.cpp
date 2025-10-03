#pragma once
#include "mainMenu.h"
#include "json.hpp"
#include <fstream>
#include <stdexcept>

mainMenu::mainMenu() {
	init();
}

void mainMenu::init() {
	loadJson(); 
	pos.setPosition((static_cast<int>(gWindowWidth) -1274)/2, (static_cast<int>(gWindowHeight) -785)/2);
	updateRenderInfo(); 
}
 
void mainMenu::loadButtons() {
  
}
void mainMenu::updateRenderInfo() {
	updateEntityRenderInfo(renderInfo, animationHandler.getCurrentTexture(), pos, animationHandler.getHeight(), animationHandler.getWidth(), getRender());
}
void mainMenu::loadJson() {
	std::string fileName = "C:\\Users\\Keary\\source\\repos\\ConsoleApplication1-working\\ConsoleApplication1\\menuJsons\\main_menu.json";
	std::ifstream file(fileName);
	if (!file.is_open()) {
		logManager::logThis("Couldn't open pause menu .json");
		throw std::runtime_error("Failed to open mainMenu.JSON: " + fileName);
	}
	nlohmann::ordered_json j;
	file >> j;
	from_json(j, *this);
}

void mainMenu::update(inputManager& input) {
	bool clicked = false;
	for (auto& btn : buttons) {
		btn.update(input);
		if (btn.wasClicked()) {
			clickedButtons.push_back(btn.getButData());
			clicked = true;
			break;
		}
	}
	if (clicked) {
		if (clickedButtons.back().action == butEnum::CLOSEMENU) {
			requestClose();
		}
	}
	animationHandler.step();
	updateEntityRenderInfo(renderInfo, animationHandler.getCurrentTexture(), pos, animationHandler.getHeight(), animationHandler.getWidth(), render);

}

