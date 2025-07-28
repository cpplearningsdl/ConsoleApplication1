#pragma once

#include <string>
#include <SDL3/SDL.h>

class renderer {
public:
	static renderer& getInstance();

	bool init(int width, int height);
	void shutdown();

	void clearNextFrame(); // Clears the off-screen frame
	void drawToNextFrame(const std::string& key, int x, int y); // Draws a texture
	void presentFrame(); // Copies next frame to screen

	void drawScreen(); // Clears nextFrame and presents it to screen (convenience)

	SDL_Renderer* getSDLRenderer();

private:
	renderer();
	~renderer();

	renderer(const renderer&) = delete;
	renderer& operator=(const renderer&) = delete;

	SDL_Renderer* sdlRenderer = nullptr;
	SDL_Texture* nextFrame = nullptr;

	int screenWidth = 0;
	int screenHeight = 0;
};
