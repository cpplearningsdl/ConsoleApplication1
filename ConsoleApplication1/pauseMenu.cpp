#pragma once
#include "pauseMenu.h"
#include "json.hpp"
#include <fstream>
#include <stdexcept>

pauseMenu::pauseMenu() {
	init();   
} 

void pauseMenu::init() {
	//this isn't quite right, the json is not up to date thats why using other function calls here for animhandler
	loadJson();
	loadButtons();
	animationHandler.setEntityName("pause_menu_background"); 
	animationHandler.loadAnimation("idle");
	pos.setPosition(552, 100);
	updateRenderInfo(); 
	buttonSpillGuts(buttons.back());
	nlohmann::ordered_json j;
	to_json(j, *this);
	logManager::logThis("Dump pause Menu: \n", j.dump(4));
}

//	buttonObj(position pos, position sz, std::function<void()> cb, std::string newName, std::string animationName, bool visible )
void pauseMenu::loadButtons() {
	//change this from emplace to push so setbuttonmenudata doesn't need to be restricted to the last entry in buttons vector
	buttons.emplace_back(
		position{ 582, 150 }, dimensions{ 188, 88 }, 
		"resume_button",
		"idle",
		true
	); 
	setButtonActionData(buttons, morphToCloseButton(1));
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
	std::string fileName = "C:\\Users\\spyse\\source\\repos\\cpplearningsdl\\ConsoleApplication1\\ConsoleApplication1\\menuJsons\\pause_menu_background.json";
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

