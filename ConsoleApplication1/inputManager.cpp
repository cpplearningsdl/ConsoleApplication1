	#include "inputManager.h"
#include "windowManager.h"
#include "windowSettings.h"
#include "renderer.h"
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
	mouseReleased = false;
	keyPressed.fill(false);
	keyReleased.fill(false); 
	eventTypesThisFrame.clear();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		eventTypesThisFrame.push_back(event.type);
		adjustMouseEventToLogical(event);

		switch (event.type) {
		case SDL_EVENT_QUIT:
			lm::logThis("Quit event received. Closing window.");
			lm::logThis("\n");
			windowManager::initWindowManager().closeWindow();
			return false;

		case SDL_EVENT_KEY_DOWN: {
			SDL_Scancode sc = event.key.scancode; 
			if (!keyStates[sc]) keyPressed[sc] = true;
			keyStates[sc] = true;
			lm::logThis("Key down: " +  std::string(SDL_GetScancodeName(sc)));
			lm::logThis("========");
			lm::logThis("ScanCode: " + std::to_string(sc));
			lm::logThis("========");
			break;
		}

		case SDL_EVENT_KEY_UP: {
			SDL_Scancode sc = event.key.scancode; 
			keyStates[sc] = false;
			keyReleased[sc] = true;
			lm::logThis("Key up: " + std::string(SDL_GetScancodeName(sc)));
			lm::logThis("========");
			lm::logThis("ScanCode: " + std::to_string(sc));
			lm::logThis("========");
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
			lm::logThis("Mouse at: (" + std::to_string(event.motion.x) + ", " + std::to_string(event.motion.y) + ")");
			break;

		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (event.button.button < mouseButtons.size())
				mouseReleased = true;
				mouseButtons[event.button.button] = false;
				lm::logThis("Mouse button up: " + std::to_string(event.button.button));
				lm::logThis("Mouse at: (" + std::to_string(event.motion.x) + ", " + std::to_string(event.motion.y) + ")");
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			updateWindowSize(windowManager::initWindowManager().getWindow());
			break;

		default:
			break;
		}
	}
	return true;
}
 
void inputManager::adjustMouseEventToLogical(SDL_Event& e) {
	switch (e.type) {
	case SDL_EVENT_MOUSE_MOTION:
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	case SDL_EVENT_MOUSE_BUTTON_UP: { 
		SDL_ConvertEventToRenderCoordinates(renderer::getInstance().getSDLRenderer(), &e);
		break;
	}
	default:
		break;
	}
}

