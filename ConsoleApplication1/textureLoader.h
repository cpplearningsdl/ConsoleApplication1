#pragma once

#include "textureDataStruct.h"
#include <string>

class textureLoader {
public:
	static bool load(const std::string& imagePath,
		const std::string& jsonPath,
		SDL_Renderer* renderer,
		textureDataStruct& outData);
};
