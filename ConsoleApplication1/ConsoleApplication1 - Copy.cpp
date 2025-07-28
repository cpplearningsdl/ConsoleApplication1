#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include "windowManager.h"
#include "logManager.h"

int main(int argc, char* argv[]) {
	std::string input;
	bool programRunning;

	programRunning = SDL_Init(SDL_INIT_VIDEO);
	
	if (!programRunning) {
		logManager::logThis("SDL Failed to initialize.");
		std::cin >> input;
		return 1;
	}
	logManager::logThis("SDL launched successfully.");
	windowManager& windowManager = windowManager::create("SDL3 Window", 800, 600);

	SDL_Delay(3000);
	std::getline(std::cin, input);

	windowManager.destroyWindow();
	SDL_Quit();

	return 0;
}