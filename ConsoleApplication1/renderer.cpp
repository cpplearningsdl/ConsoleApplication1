#include "renderer.h"
#include "windowManager.h"
#include "textureManager.h"
#include "textureDataStruct.h"
#include "windowSettings.h"
#include "logManager.h"

#define lm logManager

const int logicalW = 800;
const int logicalH = 600;

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

	return nextFrame != nullptr;
}

//bool renderer::init(int width, int height) {
//	screenWidth = width;
//	screenHeight = height;
//
//	SDL_Window* window = windowManager::initWindowManager().getWindow();
//	if (!window) {
//		lm::logThis("renderer couldn't get window");
//		return false;
//	}
//
//	sdlRenderer = windowManager::initWindowManager().getRenderer();
//	if (!sdlRenderer) { 
//		lm::logThis("couldn't create renderer");
//		return false;
//	}
//
//	lm::logThis("created renderer");
//
//	nextFrame = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888,
//		SDL_TEXTUREACCESS_TARGET, screenWidth, screenHeight);
//	return nextFrame != nullptr;
//}

void renderer::shutdown() {
	if (nextFrame) {
		SDL_DestroyTexture(nextFrame);
		nextFrame = nullptr;
	}

	if (sdlRenderer) {
		SDL_DestroyRenderer(sdlRenderer);
		sdlRenderer = nullptr;
	}
}

void renderer::clearNextFrame() {
	SDL_SetRenderTarget(sdlRenderer, nextFrame);
	SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
	SDL_RenderClear(sdlRenderer);
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
