#include "renderer.h"
#include "windowManager.h"
#include "textureManager.h"
#include "textureDataStruct.h"
#include "windowSettings.h" 
#include "logManager.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <windows.h>
#define lm logManager
  
renderer::renderer() {}
renderer::~renderer() { shutdown(); }

renderer& renderer::getInstance() {
	static renderer instance;
	return instance;
}

bool renderer::init(int width, int height) {
	screenWidth = width;
	screenHeight = height;

	SDL_Window* window = windowManager::initWindowManager().getWindow();
	if (!window) {
		lm::logThis("renderer couldn't get window");
		return false;
	}

	sdlRenderer = windowManager::initWindowManager().getRenderer();
	if (!sdlRenderer) {
		lm::logThis("couldn't get renderer");
		return false;
	}
	lm::logThis("created renderer");
	 
	SDL_SetRenderLogicalPresentation(sdlRenderer, logicalW, logicalH, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	 
	nextFrame = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, logicalW, logicalH);
	//SDL_SetTextureBlendMode(nextFrame, SDL_BLENDMODE_BLEND);
	//SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
 
	if (TTF_Init() != 1) {
		logManager::logThis("TTF_Init Failed to initialize.", SDL_GetError());
		std::cerr << "TTF_Init failed: " << SDL_TTF_GetError() << std::endl; 
		return false;
	}
	logManager::logThis("TTF_Init launched successfully.");
	return nextFrame != nullptr;
}
 
void renderer::shutdown() { 
	for (auto &p : myFonts) {
		if (p.second) TTF_CloseFont(p.second);
	}
	myFonts.clear();

	if (nextFrame) {
		SDL_DestroyTexture(nextFrame);
		nextFrame = nullptr;
	}

	if (sdlRenderer) {
		SDL_DestroyRenderer(sdlRenderer);
		sdlRenderer = nullptr;
	}


	TTF_Quit();
	SDL_Quit();
}
bool renderer::loadFont(const std::string& fontId, const std::string& fontPath, float ptsize) {
	// If already loaded with same id, close it first
	auto it = myFonts.find(fontId);
	if (it != myFonts.end() && it->second) {
		TTF_CloseFont(it->second);
		it->second = nullptr;
	}

	// TTF_OpenFont signature in SDL3_ttf: TTF_Font* TTF_OpenFont(const char* file, float ptsize);
	TTF_Font* f = TTF_OpenFont(fontPath.c_str(), ptsize);
	if (!f) { 
		return false;
	}

	myFonts[fontId] = f;
	return true;
}
void renderer::unloadFont(const std::string& fontId) {
	auto it = myFonts.find(fontId);
	if (it != myFonts.end()) {
		if (it->second) {
			TTF_CloseFont(it->second);
		}
		myFonts.erase(it);
	}
}
void renderer::clearNextFrame() {
	SDL_SetRenderTarget(sdlRenderer, nextFrame);
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
	SDL_RenderClear(sdlRenderer);
}

SDL_Texture* renderer::createTextTexture(const std::string& text, const std::string& fontId, SDL_Color color) {
	if (!sdlRenderer) return nullptr;

	auto it = myFonts.find(fontId);
	if (it == myFonts.end() || it->second == nullptr) {
		lm::logThis("create text texture error, font not loaded; id: ", fontId);
		return nullptr;
	}

	TTF_Font* font = it->second;

	// TTF_RenderText_Blended signature (SDL3_ttf wiki):
	// SDL_Surface * TTF_RenderText_Blended(TTF_Font *font, const char *text, size_t length, SDL_Color fg);
	// Passing length = 0 means null-terminated.
	SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), 0, color);
	if (!surf) {
		lm::logThis("render text blended error.");
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(sdlRenderer, surf);
	SDL_DestroySurface(surf); // SDL3: destroy surface
	if (!tex) {
		lm::logThis("SDL_CreateTextureFromSurface failed: ", SDL_GetError());
	}
	return tex;
}
void renderer::drawText(const std::string& text, const std::string& fontId, SDL_Color color, float x, float y) {
	SDL_Texture* tex = createTextTexture(text, fontId, color);
	if (!tex) return;

	float w = 0, h = 0;
	SDL_GetTextureSize(tex, &w, &h); // SDL3: fills ints w/h
	SDL_FRect dst{ x, y, w, h };
	SDL_RenderTexture(sdlRenderer, tex, nullptr, &dst);
	SDL_DestroyTexture(tex);
}

void renderer::drawToNextFrame(SDL_Texture* t, float x, float y, int h, int w) {
	 
	SDL_SetRenderTarget(sdlRenderer, nextFrame);

	SDL_FRect dst;
	dst.x = (x);
	dst.y = (y);
	dst.w = static_cast<float>(w);
	dst.h = static_cast<float>(h);

	SDL_RenderTexture(sdlRenderer, t, nullptr, &dst);
}

void renderer::presentFrame() { 
		SDL_SetRenderTarget(sdlRenderer, nullptr);
		SDL_RenderTexture(sdlRenderer, nextFrame, nullptr, nullptr);
		SDL_RenderPresent(sdlRenderer); 
}

void renderer::drawScreen() {
	presentFrame();
	clearNextFrame(); 
}

SDL_Renderer* renderer::getSDLRenderer() {
	return sdlRenderer;
}
