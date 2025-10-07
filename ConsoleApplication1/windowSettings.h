#pragma once  
#include <SDL3/SDL.h>

extern int gWindowWidth;
extern int gWindowHeight;
extern const int logicalH;
extern const int logicalW;

void updateWindowSize(SDL_Window* window);
