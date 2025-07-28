#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include "windowManager.h"

int main(int argc, char* argv[]) {
	std::string input;
	bool programRunning;

	programRunning = SDL_Init(SDL_INIT_VIDEO);
	std::cout << "Attempted to initiate SDL, programRunning = " << programRunning;

	if (!programRunning) {
		std::cout << "SDL Failed to initialize.";
		std::cin >> input;
		return 1;
	}
	 
	windowManager& windowManager = windowManager::getInstance();
	if (!windowManager.createWindow("SDL3 Window", 800, 600)) { 
		SDL_Quit();
		return 1;
	}

	SDL_Delay(3000);
	std::getline(std::cin, input);

	windowManager.destroyWindow();
	SDL_Quit();

	return 0;
}
