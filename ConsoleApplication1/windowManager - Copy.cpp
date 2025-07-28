#include "windowManager.h"
#include "logManager.h"

windowManager& windowManager::create(const std::string& title, int width, int height) {
	static windowManager instance(title, width, height);
	return instance;
}

windowManager::windowManager(const std::string& title, int width, int height) : window(nullptr) {
	window = SDL_CreateWindow(title.c_str(), width, height, 0);
	if (!window) {
		logManager::logThis("Failed to create window.");
	}
	logManager::logThis("Created window.");
}

windowManager::~windowManager() {
	destroyWindow();
}

SDL_Window* windowManager::getWindow() const {
	return window;
}

void windowManager::destroyWindow() {
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
		logManager::logThis("Window destroyed.");
	}
}
