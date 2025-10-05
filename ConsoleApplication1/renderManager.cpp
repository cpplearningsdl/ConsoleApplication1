#include "renderManager.h"
#include "entityRenderInfo.h"


void renderManager::renderMainMenu(menuManager& m) {
	for (const auto& menu : m.getMenus()) {
		if (!menu->isVisible()) continue;
		 
		const entityRenderInfo& menuInfo = menu->getEntityRenderInfo();
		renderer::getInstance().drawToNextFrame( menuInfo.tex, menuInfo.pos.getX(), menuInfo.pos.getY(), menuInfo.height, menuInfo.width ); 
		 
		for (const auto& button : menu->getButtons()) {
			const entityRenderInfo& btnInfo = button.getEntityRenderInfo();
			renderer::getInstance().drawToNextFrame( btnInfo.tex,	btnInfo.pos.getX(),	btnInfo.pos.getY(), btnInfo.height, btnInfo.width	);
		}
	} 
}

void renderManager::renderBackground() {
	SDL_Texture* tex = textureManager::getInstance().getFrame("background_idle_0");
	renderer::getInstance().drawToNextFrame(tex, 0, 0, 600, 800);
}
void renderManager::renderEntities(game& g) { 
	 
	const auto& renderables = g.getRenderableEntities(); 
	//also need to add function for converting map position to x/y position as well
	for (auto& e : renderables) {
		const entityRenderInfo& i = e->getRenderInfo(); 
		renderer::getInstance().drawToNextFrame(i.tex, i.pos.getX(), i.pos.getY(), i.height, i.width);
	}
}


void renderManager::renderGame(game& g, menuManager& m) {
	renderBackground();
	renderEntities(g); 
	//renderGameMenu(g);
	renderMainMenu(m);
	renderer::getInstance().drawScreen();
} 