#pragma once
#include <unordered_map>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class renderer {
public:
	static renderer& getInstance();

	bool init(int width, int height);
	void shutdown();

	void clearNextFrame(); 
	void drawToNextFrame(SDL_Texture* t, float x, float y, float h, float w);
	void presentFrame();  

	void drawScreen();
	SDL_Texture* createTextTexture(const std::string& text, const std::string& fontId, SDL_Color color);
	void drawText(const std::string& text, const std::string& fontId, SDL_Color color, float x, float y);

	SDL_Renderer* getSDLRenderer();

private:
	renderer();
	~renderer();

	renderer(const renderer&) = delete;
	renderer& operator=(const renderer&) = delete;
	std::unordered_map<std::string, TTF_Font*> myFonts; 
	SDL_Renderer* sdlRenderer = nullptr;
	SDL_Texture* nextFrame = nullptr;
	SDL_Texture* lightMask = nullptr;
	SDL_Texture* radialLightTexture = nullptr;
	int screenWidth = 0;
	int screenHeight = 0;
};
