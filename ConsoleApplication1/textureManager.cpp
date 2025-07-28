#include "textureManager.h"
#include "textureLoader.h"
#include "textureDataStruct.h"
#include "logManager.h"
#include <filesystem>
#include <iostream>
#define lm logManager

namespace fs = std::filesystem;

textureManager& textureManager::getInstance() {
	static textureManager instance;
	return instance;
}

bool textureManager::loadAllTextures(const std::string& rootDirectory, SDL_Renderer* renderer) {
	for (const auto& entry : fs::recursive_directory_iterator(rootDirectory)) {
		if (entry.is_regular_file() && entry.path().extension() == ".png") {
			std::string imagePath = entry.path().string();
			std::string baseName = entry.path().stem().string(); 
			std::string parentFolder = entry.path().parent_path().filename().string();
			//std::string key = parentFolder + "/" + baseName;
			std::string key = baseName;
			std::string jsonPath = (entry.path().parent_path() / (baseName + ".json")).string();

			textureDataStruct texData;
			if (textureLoader::load(imagePath, jsonPath, renderer, texData)) {
				texData.key = key;  // Store key for reference
				activeTextures[key] = std::move(texData);
				lm::logThis("Loaded art asset, key: ", key);
				//std::cout << "[textureManager] Loaded: " << key << "\n";
			}
			else {
				lm::logThis("Failed to loadart asset, key: ", key);
				//std::cerr << "[textureManager] Failed to load: " << key << "\n";
			}
		}
	}
	lm::logThis("Loaded art succesfully.");
	return true;
}

const textureDataStruct* textureManager::getTexture(const std::string& key) const {
	auto it = activeTextures.find(key);
	return (it != activeTextures.end()) ? &it->second : nullptr;
}

void textureManager::logTextureInfo(const std::string& key) const {
	auto it = activeTextures.find(key);
	if (it == activeTextures.end()) {
		lm::logThis("Texture key not found: " + key);
		return;
	}

	const textureDataStruct& tex = it->second;

	lm::logThis("Key: " + tex.key);
	lm::logThis("Animation: " + tex.animationName);
	lm::logThis("Width: " + std::to_string(tex.width));
	lm::logThis("Height: " + std::to_string(tex.height));
	lm::logThis("Frame #: " + std::to_string(tex.frameNumber));
	lm::logThis("Total Frames: " + std::to_string(tex.totalFrames));
	lm::logThis("X Offset: " + std::to_string(tex.xOffset));
	lm::logThis("Y Offset: " + std::to_string(tex.yOffset));
	lm::logThis("Loop: " + std::string(tex.loop ? "true" : "false"));
	lm::logThis("Chain Animation: " + tex.chainAnimation);
}

void textureManager::cleanUp() {
	for (auto&[key, data] : activeTextures) {
		if (data.texture) {
			SDL_DestroyTexture(data.texture);
		}
	}
	activeTextures.clear();
}

textureManager::~textureManager() {
	cleanUp();
}
