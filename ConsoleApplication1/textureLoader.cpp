#include "logManager.h"
#include "textureLoader.h"
#include "textureDataStruct.h"
#include <SDL3_image/SDL_image.h>
#include <json.hpp>
#include <fstream>
#include <iostream>
#define lm logManager


bool textureLoader::load(const std::string& imagePath,
	const std::string& jsonPath,
	SDL_Renderer* renderer,
	textureDataStruct& outData) {
	// Load PNG texture
	SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath.c_str());
	if (!texture) {
		lm::logThis("Failed to open texture file: ", imagePath.c_str());
		std::cerr << "Failed to load texture: " << imagePath << "\n";
		return false;
	}
	 
	outData.texture = texture;
	 
	std::ifstream file(jsonPath);
	if (!file.is_open()) {
		lm::logThis("Failed to open .json: ", jsonPath);
		std::cerr << "Failed to open JSON file: " << jsonPath << "\n";
		SDL_DestroyTexture(texture);
		return false;
	}

	nlohmann::json json;
	file >> json;

	// Fill out TextureData fields
	outData.animationName = json.value("animationName", "");
	outData.width = json.value("width", 0);
	outData.height = json.value("height", 0);
	outData.frameNumber = json.value("frameNumber", 0);
	outData.totalFrames = json.value("totalFrames", 0);
	outData.xOffset = json.value("xOffset", 0);
	outData.yOffset = json.value("yOffset", 0);
	outData.loop = json.value("loop", true);
	outData.chainAnimation = json.value("chainAnimation", "");

	return true;
}
