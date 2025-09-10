#include "textureManager.h"
#include "logManager.h"
#include <SDL3_image/SDL_image.h>
#include "json.hpp"
#include <cctype>
#include <string>
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


//bool textureManager::loadAllTextures(const std::string& rootDirectory, SDL_Renderer* renderer) {
//	for (const auto& entityDir : fs::directory_iterator(rootDirectory)) {
//		if (!entityDir.is_directory()) continue;
//
//		std::string entityName = entityDir.path().filename().string();
//
//		for (const auto& animDir : fs::directory_iterator(entityDir)) {
//			if (!animDir.is_directory()) continue;
//
//			std::string animationName = animDir.path().filename().string();
//			int frameCount = 0;
//
//			for (const auto& frameDir : fs::directory_iterator(animDir)) {
//				if (!frameDir.is_directory()) continue;
//
//				std::string frameFolder = frameDir.path().filename().string();
//
//				std::string pngPath;
//				std::string jsonPath;
//
//				// find .png and .json inside frame folder
//				for (const auto& file : fs::directory_iterator(frameDir)) {
//					if (file.path().extension() == ".png") {
//						pngPath = file.path().string();
//					}
//					else if (file.path().extension() == ".json") {
//						jsonPath = file.path().string();
//					}
//				}
//
//				if (pngPath.empty() || jsonPath.empty()) {
//					lm::logThis("Missing .png or .json in frame folder: " + frameDir.path().string());
//					continue;
//				}
//
//				// unique key: goblinWalk1
//				std::string frameKey = entityName + "_" + animationName + "_" + frameFolder;
//
//				// --- Load texture ---
//				SDL_Texture* tex = IMG_LoadTexture(renderer, pngPath.c_str());
//				if (!tex) {
//					lm::logThis("Failed to load texture: " + pngPath);
//					continue;
//				}
//				framesMap[frameKey] = tex;
//				lm::logThis("New frame and key", frameKey);
//
//				// --- Load JSON ---
//				std::ifstream file(jsonPath);
//				if (!file.is_open()) {
//					lm::logThis("Failed to open JSON: " + jsonPath);
//					continue;
//				}
//
//				nlohmann::json json;
//				file >> json;
//
//				textureDataStruct newFrameData;
//				newFrameData.animationName = json.value("animationName", animationName);
//				newFrameData.width = json.value("width", 0);
//				newFrameData.height = json.value("height", 0);
//				newFrameData.hitBoxWidth = json.value("hitBoxWidth", 0);
//				newFrameData.hitBoxHeight = json.value("hitBoxHeight", 0);
//				newFrameData.totalFrames = json.value("totalFrames", 0);
//				newFrameData.xOffset = json.value("xOffset", 0);
//				newFrameData.yOffset = json.value("yOffset", 0);
//				newFrameData.loop = json.value("loop", true);
//				newFrameData.chainAnimation = json.value("chainAnimation", "");
//
//				frameDataMap[frameKey] = std::move(newFrameData);
//
//				frameCount++;
//				lm::logThis("Loaded frame: " + frameKey);
//				logAnimationInfo(frameKey);
//			}
//
//			// --- Record animation membership ---
//			if (entityAnimationNamesMap.find(entityName) == entityAnimationNamesMap.end()) {
//				entityAnimationNamesMap[entityName] = animationName;
//			}
//			else {
//				entityAnimationNamesMap[entityName] += "," + animationName;
//			}
//		}
//	}
//
//	lm::logThis("Finished loading art assets.");
//	return true;
//}
//

bool textureManager::loadAllTextures(const std::string& rootDirectory, SDL_Renderer* renderer) {
	lm::logThis("Scanning root art folder: " + rootDirectory);

	for (const auto& entityDir : fs::directory_iterator(rootDirectory)) {
		if (!entityDir.is_directory()) continue;

		std::string entityName = entityDir.path().filename().string();
		lm::logThis("=== Entity folder: " + entityName);

		for (const auto& animDir : fs::directory_iterator(entityDir)) {
			if (!animDir.is_directory()) continue;

			std::string animationName = animDir.path().filename().string();
			lm::logThis("  -> Animation folder: " + animationName);

			int frameCount = 0;

			for (const auto& frameDir : fs::directory_iterator(animDir)) {
				if (!frameDir.is_directory()) continue;

				std::string frameFolder = frameDir.path().filename().string();
				lm::logThis("    -> Frame folder: " + frameFolder);

				std::string pngPath;
				std::string jsonPath;

				// find .png and .json inside frame folder
				for (const auto& file : fs::directory_iterator(frameDir)) {
					if (file.path().extension() == ".png") {
						pngPath = file.path().string();
					}
					else if (file.path().extension() == ".json") {
						jsonPath = file.path().string();
					}
				}

				if (pngPath.empty() || jsonPath.empty()) {
					lm::logThis("    !! Missing .png or .json in: " + frameDir.path().string());
					continue;
				}

				// unique key: goblin_walk_1
				std::string frameKey = entityName + "_" + animationName + "_" + frameFolder;

				// --- Load texture ---
				SDL_Texture* tex = IMG_LoadTexture(renderer, pngPath.c_str());
				if (!tex) {
					lm::logThis("    !! Failed to load texture: " + pngPath);
					continue;
				}
				framesMap[frameKey] = tex;
				lm::logThis("    Loaded texture, key=" + frameKey);

				// --- Load JSON ---
				try {
					std::ifstream file(jsonPath);
					if (!file.is_open()) {
						lm::logThis("    !! Failed to open JSON: " + jsonPath);
						continue;
					}

					nlohmann::ordered_json json;
					file >> json;

					textureDataStruct newFrameData;
					newFrameData.animationName = json.value("animationName", animationName);
					newFrameData.width = json.value("width", 0);
					newFrameData.height = json.value("height", 0);
					newFrameData.hitBoxWidth = json.value("hitBoxWidth", 0);
					newFrameData.hitBoxHeight = json.value("hitBoxHeight", 0);
					newFrameData.totalFrames = json.value("totalFrames", 0);
					newFrameData.xOffset = json.value("xOffset", 0);
					newFrameData.yOffset = json.value("yOffset", 0);
					newFrameData.loop = json.value("loop", true);
					newFrameData.chainAnimation = json.value("chainAnimation", "");

					frameDataMap[frameKey] = std::move(newFrameData);

					lm::logThis("    Loaded frame metadata: " + frameKey);
				}
				catch (const std::exception& e) {
					lm::logThis(std::string("    !! JSON parse error: ") + e.what());
					continue;
				}

				frameCount++;
			}

			// --- Record animation membership ---
			if (entityAnimationNamesMap.find(entityName) == entityAnimationNamesMap.end()) {
				entityAnimationNamesMap[entityName] = animationName;
			}
			else {
				entityAnimationNamesMap[entityName] += "," + animationName;
			}
			lm::logThis("Animation Names; ", entityAnimationNamesMap[entityName]);
			lm::logThis("  Finished animation: " + animationName + " (" + std::to_string(frameCount) + " frames)");
		}
	}

	lm::logThis("=== Finished loading ALL art assets. ===");
	return true;
}


SDL_Texture* textureManager::getFrame(const std::string& key) const {
	auto it = framesMap.find(key);
	return (it != framesMap.end()) ? it->second : nullptr;
}

const textureDataStruct* textureManager::getAnimationData(const std::string& name) const {
	auto it = frameDataMap.find(name);
	return (it != frameDataMap.end()) ? &it->second : nullptr;
}

void textureManager::logAnimationInfo(const std::string& name) const {
	auto it = frameDataMap.find(name);
	if (it == frameDataMap.end()) {
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

// Extracts the root animation name (e.g., "fireball12" -> "fireball")
std::string getAnimationRoot(const std::string& frameName) {
	std::string root = frameName;
	while (!root.empty() && std::isdigit(root.back())) {
		root.pop_back();
	}
	return root;
}

// Extracts the frame number (e.g., "fireball12" -> 12)
int getFrameNumber(const std::string& frameName) {
	int num = 0;
	int multiplier = 1;

	// Walk backward through digits and build the number
	for (int i = static_cast<int>(frameName.size()) - 1; i >= 0; --i) {
		if (std::isdigit(frameName[i])) {
			num += (frameName[i] - '0') * multiplier;
			multiplier *= 10;
		}
		else {
			break;
		}
	}
	return num;
}

void textureManager::cleanUp() {
	for (auto&[key, tex] : framesMap) {
		if (tex) {
			SDL_DestroyTexture(tex);
		}
	}
	framesMap.clear();
	frameDataMap.clear();
}

textureManager::~textureManager() {
	cleanUp();
}
