#pragma once

#include <string>
#include <SDL3/SDL.h>

struct textureDataStruct { 
	std::string key;
	std::string animationName;
	int frameNumber = 0;
	int totalFrames = 0;

	int width = 0;
	int height = 0;
	int hitBoxWidth = 0;
	int hitBoxHeight = 0;

	int actualX = 0;
	int actualY = 0;

	int currentX = 0;
	int currentY = 0;

	int xOffset = 0;
	int yOffset = 0;

	bool loop = true;
	std::string chainAnimation;
};
