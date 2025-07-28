#pragma once

#include "textureDataStruct.h"
#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>
 


class textureManager {
public:
	static textureManager& getInstance();

	// Loads all .png + .json from subfolders of rootDirectory
	bool loadAllTextures(const std::string& rootDirectory, SDL_Renderer* renderer);

	// Accessor
	const textureDataStruct* getTexture(const std::string& key) const;

	void logTextureInfo(const std::string& key) const;

	// Cleanup
	void cleanUp();

private:
	std::unordered_map<std::string, textureDataStruct> activeTextures;

	textureManager() = default;
	~textureManager();
	textureManager(const textureManager&) = delete;
	textureManager& operator=(const textureManager&) = delete;
};
