	#include "inputManager.h"
#include "windowManager.h"
#include <SDL3/SDL.h> 
#include "logManager.h"
#include <iostream> 

#define lm logManager
 
inputManager::inputManager() {
	keyStates.fill(false);
	keyPressed.fill(false);
	keyReleased.fill(false);
	mouseButtons.fill(false);
}

inputManager& inputManager::getInstance() {
	static inputManager instance;
	return instance;
}
 
 
bool inputManager::pollEvents() {
	// reset per-frame pressed/released keys
	keyPressed.fill(false);
	keyReleased.fill(false); 

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_EVENT_QUIT:
			lm::logThis("Quit event received. Closing window.");
			windowManager::initWindowManager().closeWindow();
			return false;

		case SDL_EVENT_KEY_DOWN: {
			SDL_Scancode sc = event.key.scancode; 
			if (!keyStates[sc]) keyPressed[sc] = true;
			keyStates[sc] = true;
			lm::logThis("Key down: " +  std::string(SDL_GetScancodeName(sc)));
			lm::logThis("ScanCode: " + sc);
			break;
		}

		case SDL_EVENT_KEY_UP: {
			SDL_Scancode sc = event.key.scancode; 
			keyStates[sc] = false;
			keyReleased[sc] = true;
			lm::logThis("Key up: " + std::string(SDL_GetScancodeName(sc)));
			lm::logThis("ScanCode: " + sc);
			break;
		}

		case SDL_EVENT_MOUSE_MOTION:
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			//lm::logThis("Mouse moved to: (" + std::to_string(mouseX) + ", " + std::to_string(mouseY) + ")");
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event.button.button < mouseButtons.size())
				mouseButtons[event.button.button] = true;
			lm::logThis("Mouse button down: " + std::to_string(event.button.button));
			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (event.button.button < mouseButtons.size())
				mouseButtons[event.button.button] = false;
				lm::logThis("Mouse button up: " + std::to_string(event.button.button));
			break;

		default:
			break;
		}
	}
	return true;
}
 