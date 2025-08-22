#include "textureManager.h"
#include "logManager.h"
#include <SDL3_image/SDL_image.h>
#include "json.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#define lm logManager

//using json = nlohmann::json;

namespace fs = std::filesystem; 

textureManager& textureManager::getInstance() {
	static textureManager instance;
	return instance;
}

bool textureManager::loadAllTextures(const std::string& rootDirectory, SDL_Renderer* renderer) {
	for (const auto& dirEntry : fs::directory_iterator(rootDirectory)) {
		if (!dirEntry.is_directory()) continue;

		std::string folderName = dirEntry.path().filename().string();
		std::string jsonPath = (dirEntry.path() / (folderName + ".json")).string();
		 
		std::ifstream file(jsonPath);
		if (!file.is_open()) {
			lm::logThis("Failed to open animation JSON: " + jsonPath);
			continue;
		}

		nlohmann::json json;
		file >> json;

		textureDataStruct animData;  // metadata only
		animData.animationName = json.value("animationName", folderName);
		animData.width = json.value("width", 0);
		animData.height = json.value("height", 0);
		animData.totalFrames = json.value("totalFrames", 0);
		animData.xOffset = json.value("xOffset", 0);
		animData.yOffset = json.value("yOffset", 0);
		animData.loop = json.value("loop", true);
		animData.chainAnimation = json.value("chainAnimation", "");

		animationData[folderName] = std::move(animData);
		 
		for (const auto& entry : fs::directory_iterator(dirEntry)) {
			if (entry.is_regular_file() && entry.path().extension() == ".png") {
				std::string filename = entry.path().stem().string(); 
				std::string key = filename; 

				SDL_Texture* tex = IMG_LoadTexture(renderer, entry.path().string().c_str());
				if (!tex) {
					lm::logThis("Failed to load frame: " + entry.path().string());
					continue;
				}

				frames[key] = tex;
				lm::logThis("Loaded frame: " + key);
			}
		}
	}

	lm::logThis("Finished loading art assets.");
	return true;
}



SDL_Texture* textureManager::getFrame(const std::string& key) const {
	auto it = frames.find(key);
	return (it != frames.end()) ? it->second : nullptr;
}

const textureDataStruct* textureManager::getAnimationData(const std::string& name) const {
	auto it = animationData.find(name);
	return (it != animationData.end()) ? &it->second : nullptr;
}

void textureManager::logAnimationInfo(const std::string& name) const {
	auto it = animationData.find(name);
	if (it == animationData.end()) {
		lm::logThis("Animation key not found: " + name);
		return;
	}

	const textureDataStruct& anim = it->second;

	lm::logThis("Animation: " + anim.animationName);
	lm::logThis("Width: " + std::to_string(anim.width));
	lm::logThis("Height: " + std::to_string(anim.height));
	lm::logThis("Total Frames: " + std::to_string(anim.totalFrames));
	lm::logThis("X Offset: " + std::to_string(anim.xOffset));
	lm::logThis("Y Offset: " + std::to_string(anim.yOffset));
	lm::logThis("Loop: " + std::string(anim.loop ? "true" : "false"));
	lm::logThis("Chain Animation: " + anim.chainAnimation);
}

void textureManager::cleanUp() {
	for (auto&[key, tex] : frames) {
		if (tex) {
			SDL_DestroyTexture(tex);
		}
	}
	frames.clear();
	animationData.clear();
}

textureManager::~textureManager() {
	cleanUp();
}
