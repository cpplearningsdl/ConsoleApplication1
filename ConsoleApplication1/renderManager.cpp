#include "renderManager.h"
#include "entityRenderInfo.h"


void renderManager::renderEntities(game& g) { 
	 
	const auto& renderables = g.getRenderables();

	for (auto& e : renderables) {
		const entityRenderInfo& i = e->getRenderInfo(); 
		renderer::getInstance().drawToNextFrame(i.textureKey, i.pos.getX(), i.pos.getY());
	}
}

void renderManager::renderGame(game& g) {
	renderer::getInstance().drawToNextFrame("background_idle_0", 0, 0);
	renderEntities(g);
	 
	renderer::getInstance().drawScreen();

}