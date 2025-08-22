#pragma once

#include "textureDataStruct.h"
#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>

class textureManager {
public:
	static textureManager& getInstance();

	// Loads all animations (.json) and frame textures (.png) from subfolders of rootDirectory
	bool loadAllTextures(const std::string& rootDirectory, SDL_Renderer* renderer);

	// Accessors
	SDL_Texture* getFrame(const std::string& key) const; 
	const textureDataStruct* getAnimationData(const std::string& name) const;  

	void logAnimationInfo(const std::string& name) const;

	// Cleanup
	void cleanUp();

private:
	std::unordered_map<std::string, SDL_Texture*> frames; 
	std::unordered_map<std::string, textureDataStruct> animationData; 

	textureManager() = default;
	~textureManager();
	textureManager(const textureManager&) = delete;
	textureManager& operator=(const textureManager&) = delete;
};
