#include "renderManager.h"
#include "entityRenderInfo.h"

//the key to get the texture(And animation data for that matter) are strings, should save pointers to each texture in an animation in the animationhandler then just use that and no string lookups!
void renderManager::renderMainMenu(menuManager& m) {
	for (const auto& menu : m.getMenus()) {
		if (!menu->isVisible()) continue;
		 
		const entityRenderInfo& menuInfo = menu->getEntityRenderInfo();
		renderer::getInstance().drawToNextFrame( menuInfo.textureKey, menuInfo.pos.getX(), menuInfo.pos.getY()	); 
		 
		for (const auto& button : menu->getButtons()) {
			const entityRenderInfo& btnInfo = button.getEntityRenderInfo();
			renderer::getInstance().drawToNextFrame( btnInfo.textureKey,	btnInfo.pos.getX(),	btnInfo.pos.getY()	);
		}
	} 
}

void renderManager::renderBackground() {
	renderer::getInstance().drawToNextFrame("background_idle_0", 0, 0);
}
void renderManager::renderEntities(game& g) { 
	 
	const auto& renderables = g.getRenderables();
	//right now entities animationmovement x,y offsets are not being added to getrenderinfo UPDATE IT
	//also need to add function for converting map position to x/y position as well
	for (auto& e : renderables) {
		const entityRenderInfo& i = e->getRenderInfo(); 
		renderer::getInstance().drawToNextFrame(i.textureKey, i.pos.getX(), i.pos.getY());
	}
}


void renderManager::renderGame(game& g, menuManager& m) {
	renderBackground();
	renderEntities(g); 
	//renderGameMenu(g);
	renderMainMenu(m);
	renderer::getInstance().drawScreen();
} 