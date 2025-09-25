#pragma once
#include "pauseMenu.h"
#include "json.hpp"
#include <fstream>
#include <stdexcept>

pauseMenu::pauseMenu() {
	init();   
} 

void pauseMenu::init() {
	loadJson();
	loadButtons();
	animationHandler.setEntityName("pause_menu_background"); 
	animationHandler.loadAnimation("idle");
	pos.setPosition(552, 100);
	updateRenderInfo();
}

//	buttonObj(position pos, position sz, std::function<void()> cb, std::string newName, std::string animationName, bool visible )
void pauseMenu::loadButtons() {
	buttons.emplace_back(
		position{ 582, 150 }, dimensions{ 188, 88 },
		[this]() { logManager::logThis("lambda"); if (parentMenu) { this->requestClose(); }  },
		"resume_button",
		"idle",
		true
	); 
	//buttons.emplace_back(
	//	position{ 100, 200 }, dimensions{ 200, 50 },
	//	[&]() {},
	//	"Save",
	//	"idle",
	//	true
	//);

	//buttons.emplace_back(
	//	position{ 100, 300 }, dimensions{ 200, 50 },
	//	[&]() {},
	//	"Quit",
	//	"idle",
	//	true
	//);
}
void pauseMenu::updateRenderInfo() {
	updateEntityRenderInfo(renderInfo, animationHandler.getCurrentTexture(), pos, animationHandler.getHeight(), animationHandler.getWidth(), getRender());
}
void pauseMenu::loadJson( ) {
	std::string fileName = "C:\\Users\\Keary\\source\\repos\\ConsoleApplication1-working\\ConsoleApplication1\\menuJsons\\pause_menu_background.json";
	std::ifstream file(fileName);
	if (!file.is_open()) {
		logManager::logThis("Couldn't open pause menu .json");
		throw std::runtime_error("Failed to open pauseMenu JSON: " + fileName);
	}
	nlohmann::ordered_json j;
	file >> j;
	from_json(j, *this);
}

void pauseMenu::update(inputManager& input) {
	animationHandler.step();
	updateEntityRenderInfo(renderInfo, animationHandler.getCurrentTexture(), pos, animationHandler.getHeight(), animationHandler.getWidth(), render);
	for (auto& btn : buttons) {
		btn.update(input);
	}
}