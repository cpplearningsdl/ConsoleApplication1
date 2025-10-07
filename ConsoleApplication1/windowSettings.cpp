#pragma once
 
#include "windowSettings.h"
#include <SDL3/SDL.h>
//
//int gWindowWidth = 800;
//int gWindowHeight = 600;


int gWindowWidth = 1680;
int gWindowHeight = 1050;
const int logicalW = 128 * 20;
const int logicalH = 128 * 12;

void updateWindowSize(SDL_Window* window) {
	SDL_GetWindowSize(window, &gWindowWidth, &gWindowHeight);
}
