#include "windowManager.h"

windowManager::windowManager() : window(nullptr) {}

windowManager::~windowManager() {
	destroyWindow();
}

windowManager& windowManager::getInstance() {
	static windowManager instance;
	return instance;
}

bool windowManager::createWindow(const std::string& title, int width, int height, Uint32 flags) {
	if (window) return true;
	window = SDL_CreateWindow(title.c_str(), width, height, flags);
	return window != nullptr;
}

SDL_Window* windowManager::getWindow() const {
	return window;
}

void windowManager::destroyWindow() {
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}
