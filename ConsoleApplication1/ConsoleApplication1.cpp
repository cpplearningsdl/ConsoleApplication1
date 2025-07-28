#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "windowManager.h"
#include "inputManager.h"
#include "textureManager.h"
#include "renderer.h"
#include "logManager.h"
#include "json.hpp"

using json = nlohmann::json;


int main(int argc, char* argv[]) {
	std::string input; 
	std::string windowTitle;
	int windowHeight = 600;
	int windowWidth = 800;
	 
	if (int success = SDL_Init(SDL_INIT_VIDEO) < 1) {
		logManager::logThis("SDL Failed to initialize."); 
		return 1;
	}
	logManager::logThis("SDL launched successfully.");
	 
	windowManager& windowManager = windowManager::initWindowManager();

	if (!windowManager.openWindow(windowTitle, windowWidth, windowHeight)) { 
		logManager::logThis("Failed to open window");
		return 1;
	}

	textureManager& textureManager = textureManager::getInstance();
	std::string artAssetDirectory = "C:\\Users\\Keary\\source\\repos\\ConsoleApplication1\\ConsoleApplication1\\artAssets";
	if (!textureManager.loadAllTextures(artAssetDirectory, windowManager.getRenderer())) {
		logManager::logThis("Failed to load art succesfully.");
		return 1;
	} 
	renderer& renderer = renderer::getInstance();
	renderer.init(600, 800);

	renderer.drawToNextFrame("white_piece_idle_0", 128, 128);
	renderer.drawToNextFrame("black_piece_idle_0", 0, 0);
	renderer.drawScreen();

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	bool running = true;
	int frameNumber = 1;
	bool displayFrameNumber = false;
	while (running && windowManager.getWindow()) {
		Uint64 frameStart = SDL_GetTicks();
		if(displayFrameNumber) logManager::logThis("Frame start ", frameNumber);

		// 1. Input
		running = inputManager::getInstance().pollEvents();

		// 2. Update (placeholder)
		// game.update();

		// 3. Render (placeholder)
		// game.render();

		// 4. Timing
		Uint64 frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) {
			SDL_Delay(static_cast<Uint32>(frameDelay - frameTime));
		}
		frameNumber++;
	}
	textureManager.logTextureInfo("white_piece_idle_0");




	SDL_Delay(3000);
	std::getline(std::cin, input);

	windowManager.closeWindow();
	SDL_Quit();

	return 0;
}