	#include "inputManager.h"
#include "windowManager.h"
#include <SDL3/SDL.h>
#include "logManager.h"
#include <iostream>

#define lm logManager

inputManager& inputManager::getInstance() {
	static inputManager instance;
	return instance;
}
 

bool inputManager::pollEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		std::cout << "SDL_Event: " << event.type << "\n";
		if (event.type == SDL_EVENT_QUIT) {
			lm::logThis("Quit event received. Closing window.");
			windowManager::initWindowManager().closeWindow();  // or destroyWindow()
			return false;
		}
		// Additional input handling here (keyboard, mouse, etc.)

		return true;
	}
	return true;
}
