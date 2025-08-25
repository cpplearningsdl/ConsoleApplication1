#pragma once

#include <string>
#include <SDL3/SDL.h>

struct textureDataStruct { 
	std::string key;
	std::string animationName;

	int width = 0;
	int height = 0;

	int frameNumber = 0;
	int totalFrames = 0;

	int xOffset = 0;
	int yOffset = 0;

	bool loop = true;
	std::string chainAnimation;
};
