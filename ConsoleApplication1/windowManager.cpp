#include "windowManager.h"
#include "logManager.h"
#include <SDL3/SDL_render.h>
#include <iostream>
#define lm logManager

windowManager& windowManager::initWindowManager() {
	static windowManager instance;
	return instance;
}

windowManager::windowManager() : window(nullptr) {}

bool windowManager::openWindow(const std::string& title, int width, int height, Uint32 flags) {
	if (window) return true; 

	window = SDL_CreateWindow(title.c_str(), width, height, flags);
	if (!window) {
		lm::logThis("Failed to create window.");
		return false;
	}

	renderer = SDL_CreateRenderer(window, nullptr);
	if (!renderer) {
		lm::logThis("Failed to create renderer.");
		SDL_DestroyWindow(window);
		window = nullptr;
		return false;
	}

	lm::logThis("Created window.");
	return true;
}

windowManager::~windowManager() {
	closeWindow();
}

SDL_Window* windowManager::getWindow() const {
	return window;
}

SDL_Renderer* windowManager::getRenderer() const {
	return renderer;
}

void windowManager::closeWindow() {
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
		lm::logThis("Destroyed window.");
	}
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		lm::logThis("Destroyed renderer.");
	}
}
