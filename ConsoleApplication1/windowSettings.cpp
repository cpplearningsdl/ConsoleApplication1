#pragma once
 
#include "windowSettings.h"
#include <SDL3/SDL.h>

int gWindowWidth = 800;
int gWindowHeight = 600;

void updateWindowSize(SDL_Window* window) {
	SDL_GetWindowSize(window, &gWindowWidth, &gWindowHeight);
}
