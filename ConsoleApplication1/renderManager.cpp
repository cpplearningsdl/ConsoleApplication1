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
	
	const viewPort& view = g.getView();  
	const float camX = view.viewPos.getX();
	const float camY = view.viewPos.getY();
	const auto& renderables = g.getRenderableEntities(); 

	for (auto& e : renderables) {
		const entityRenderInfo& i = e->getRenderInfo(); 
		const float screenX = i.pos.getX() - camX;
		const float screenY = i.pos.getY() - camY;
		renderer::getInstance().drawToNextFrame(i.tex, screenX, screenY, i.height, i.width);
	}
}


void renderManager::renderGame(game& g, menuManager& m) {
	renderBackground();
	renderEntities(g); 
	//renderGameMenu(g);
	renderMainMenu(m);
	renderer::getInstance().drawScreen();
} 