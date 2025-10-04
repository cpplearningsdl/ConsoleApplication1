#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "gameManager.h"
#include "windowManager.h"
#include "windowSettings.h"
#include "menuManager.h"
#include "mainMenu.h"
#include "inputManager.h"
#include "textureManager.h"
#include "renderer.h"
#include "logManager.h"
#include "json.hpp"

using json = nlohmann::ordered_json;
//fucking check all directory paths for spaces and consider using std::string R"path", no escape characters OR
//std::filesystem::path exePath = std::filesystem::current_path(); // or path of executable
//std::filesystem::path assetsDir = exePath / "assets";

int main(int argc, char* argv[]) {
	std::string input; 
	std::string windowTitle;
	//int windowHeight = 600;
	//int windowWidth = 800;
	 
	if (int success = SDL_Init(SDL_INIT_VIDEO) < 1) {
		logManager::logThis("SDL Failed to initialize."); 
		return 1;
	}
	logManager::logThis("SDL launched successfully.");
	 
	windowManager& windowManager = windowManager::initWindowManager();

	if (!windowManager.openWindow(windowTitle, gWindowWidth, gWindowHeight)) { 
		logManager::logThis("Failed to open window");
		return 1;
	}

	textureManager& textureManager = textureManager::getInstance();
	std::string artAssetDirectory = "C:\\Users\\Keary\\source\\repos\\ConsoleApplication1-working\\ConsoleApplication1\\artAssets";
	if (!textureManager.loadAllTextures(artAssetDirectory, windowManager.getRenderer())) {
		logManager::logThis("Failed to load art succesfully.");
		return 1;
	} 
	renderer& renderer = renderer::getInstance();
	renderer.init(600, 800);
 

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	bool running = true;
	bool startedGame = false;
	int frameNumber = 1;
	bool displayFrameNumber = false; 

	gameManager::getInstance().loadDefaultAssets();
	gameManager::getInstance().newGame(); 
	 
	menuManager theStartMenu;
	theStartMenu.openMenu(std::make_unique<mainMenu>());

	while (running && windowManager.getWindow()) {
		Uint64 frameStart = SDL_GetTicks();
		if(displayFrameNumber) logManager::logThis("Frame start ", frameNumber);

		if (frameNumber == 1) { }
		// 1. Input
		running = inputManager::getInstance().pollEvents();



		gameManager::getInstance().processGame();
 
		Uint64 frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) {
			SDL_Delay(static_cast<Uint32>(frameDelay - frameTime));
		}
		frameNumber++;
	} 




	SDL_Delay(3000);
	std::getline(std::cin, input);

	windowManager.closeWindow();
	SDL_Quit();

	return 0;
}