#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "json.hpp"
#include "SDL_Fpoint_json.h"

struct emberParticleBatch {
	std::vector<SDL_FPoint> points;
	std::vector<SDL_Color> colors; 
};