#include "renderManager.h"


void renderManager::renderEntities(game& g) { 

	std::vector<entity*> renderables = g.getRenderables();

	for (auto& e : renderables) {
		std::string key = e->getAnimationManager().getTextureKey(); 
		renderer::getInstance().drawToNextFrame(key, 0, 0);
	}
}

void renderManager::renderGame(game& g) {
	renderer::getInstance().drawToNextFrame("background_idle_0", 0, 0);
	renderEntities(g);


	renderer::getInstance().drawScreen();

}