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
	pos.setPosition((static_cast<float>(logicalW) -1274)/2, (static_cast<float>(logicalH) -785)/2);
	loadButtons(); 
	updateRenderInfo(); 
	show();
}
 
void mainMenu::loadButtons() {
	//THIS MENU LOADED BY JSON BUT SETTING POS HERE UNTIL DEFINITIVE LOGICALSIZE..
	dimensions p = buttons.back().getSize();
	position n = { (static_cast<float>(logicalW) - static_cast<float>(p.getW())) / 2.0f,(static_cast<float>(logicalH) - static_cast<float>(p.getH())) / 3.0f };
	logManager::logThis("ButtonArraySize: ", buttons.size());
	buttons.back().setPos(n);
}
void mainMenu::updateRenderInfo() {
	updateEntityRenderInfo(renderInfo, animationHandler.getCurrentTexture(), pos, animationHandler.getHeight(), animationHandler.getWidth(), getRender());
}
void mainMenu::loadJson() {
	std::string fileName = "C:\\Users\\Keary\\source\\repos\\ConsoleApplication1-working\\ConsoleApplication1\\menuJsons\\start_menu.json";
	std::ifstream file(fileName);
	if (!file.is_open()) {
		logManager::logThis("Couldn't open start menu .json");
		throw std::runtime_error("Failed to open start menu.JSON: " + fileName);
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

