#include "renderer.h"
#include "windowManager.h"
#include "textureManager.h"
#include "textureDataStruct.h"
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

void renderer::drawToNextFrame(const std::string& key, int x, int y) {
	const textureDataStruct* texData = textureManager::getInstance().getAnimationData(key);
	SDL_Texture* tex = textureManager::getInstance().getFrame(key);
	//SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

	if (!texData || !tex) { 
		logManager::logThis("Failure loading texture meta data or texture "); 
		return;
	}

	SDL_SetRenderTarget(sdlRenderer, nextFrame);

	SDL_FRect dst;
	dst.x = static_cast<float>(x);
	dst.y = static_cast<float>(y);
	dst.w = static_cast<float>(texData->width);
	dst.h = static_cast<float>(texData->height);

	SDL_RenderTexture(sdlRenderer, tex, nullptr, &dst);
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
