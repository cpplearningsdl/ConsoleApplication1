#include "renderManager.h"


void renderManager::renderEntities(game& g) { 

	std::vector<entity*> renderables = g.getRenderables();

	for (auto& e : renderables) {
		std::string key = e->getAnimationManager().getTextureKey();
		logManager::logThis("Rendering key: ", key);
		renderer::getInstance().drawToNextFrame(key, 0, 0);
	}
}