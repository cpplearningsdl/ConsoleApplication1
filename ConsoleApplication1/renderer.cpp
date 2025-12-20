#include "renderer.h"
#include "windowManager.h"
#include "textureManager.h"
#include "fontManager.h"
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
	radialLightTexture = textureManager::getInstance().getFrame("light_gradiants_light_circle_longtail_512_0");
	SDL_SetTextureBlendMode(radialLightTexture, SDL_BLENDMODE_ADD);

	if (TTF_Init() != 1) {
		logManager::logThis("TTF_Init Failed to initialize.", SDL_GetError()); 
		return false;
	}
	logManager::logThis("TTF_Init launched successfully.");
	return nextFrame != nullptr;
}
 
void renderer::shutdown() {  
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
 
void renderer::clearNextFrame() {
	SDL_SetRenderTarget(sdlRenderer, nextFrame);
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
	SDL_RenderClear(sdlRenderer);
}

SDL_Texture* renderer::createTextTexture(const std::string& text, const std::string& fontId, SDL_Color color) {
	if (!sdlRenderer) return nullptr;

	TTF_Font* font = fontManager::getInstance().getFont(fontId);
	if (!font) return nullptr;

	SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), text.length(), color);
	if (!surf) {
		lm::logThis("TTF_RenderText_Blended error:", SDL_GetError());
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(sdlRenderer, surf);
	SDL_DestroySurface(surf);
	if (!tex) {
		lm::logThis("SDL_CreateTextureFromSurface failed: ", SDL_GetError());
	}
	return tex;
}
void renderer::drawText(const std::string& text, const std::string& fontId, SDL_Color color, float x, float y) {
	SDL_Texture* tex = createTextTexture(text, fontId, color);
	if (!tex) return;
		
	float w = 0, h = 0;
	SDL_GetTextureSize(tex, &w, &h);
	SDL_FRect dst{ x, y, w, h };

	SDL_SetRenderTarget(sdlRenderer, nextFrame);
	SDL_RenderTexture(sdlRenderer, tex, nullptr, &dst);

	SDL_DestroyTexture(tex);
}


void renderer::drawToNextFrame(SDL_Texture* t, float x, float y, float h, float w) {
	 
	SDL_SetRenderTarget(sdlRenderer, nextFrame);

	SDL_FRect dst;
	dst.x = (x);
	dst.y = (y);
	dst.w = w;
	dst.h = h;

	SDL_RenderTexture(sdlRenderer, t, nullptr, &dst);
}


void renderer::drawAmbientDarkness(Uint8 alpha) {
	SDL_SetRenderTarget(sdlRenderer, nextFrame);
	SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, alpha);

	SDL_FRect full{ 0, 0, (float)logicalW, (float)logicalH };
	SDL_RenderFillRect(sdlRenderer, &full);
}


//void renderer::drawLight(float x, float y, float radius, SDL_Color color, float intensity){
//	SDL_SetRenderTarget(sdlRenderer, nextFrame); 
//	SDL_SetTextureColorMod(radialLightTexture, color.r, color.g, color.b);
//	SDL_SetTextureAlphaMod(radialLightTexture, (Uint8)(255 * intensity)); 
//	SDL_FRect dst{
//		x - radius,
//		y - radius,
//		radius * 2,
//		radius * 2
//	};
//
//	SDL_RenderTexture(sdlRenderer, radialLightTexture, nullptr, &dst);
//}

void renderer::drawLight(float x, float y, float radius, SDL_Color color, float intensity){
	SDL_SetRenderTarget(sdlRenderer, nextFrame);

	Uint8 i = (Uint8)(255 * intensity);

	SDL_SetTextureColorMod(radialLightTexture, (color.r * i) / 255, (color.g * i) / 255, (color.b * i) / 255);
	 

	SDL_FRect dst{
		x - radius,
		y - radius,
		radius * 2,
		radius * 2
	};

	SDL_RenderTexture(sdlRenderer, radialLightTexture, nullptr, &dst);
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
