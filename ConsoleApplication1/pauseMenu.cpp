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
	animationHandler.setEntityName("pause_menu_background");//WHY ISNT THIS THE KEY THE FIRST FRAME MENU IS OPEN?
	animationHandler.setAnimationName("idle");
	pos.setPosition(10, 100);
}

//	buttonObj(position pos, position sz, std::function<void()> cb, std::string newName, std::string animationName, bool visible )
void pauseMenu::loadButtons() {
	buttons.emplace_back(
		position{ 100, 100 }, dimensions{ 200, 50 },
		[&]() {  hide(); },
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
	updateEntityRenderInfo(renderInfo, animationHandler.getTextureKey(), pos, render);
	for (auto& btn : buttons) {
		btn.update();
	}
}