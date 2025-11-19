#include "renderManager.h"
#include "entityRenderInfo.h"
#include "windowSettings.h"


void renderManager::renderMainMenu(menuManager& m) {

	for (const auto& menu : m.getMenus()) {
		
		if (!menu->isVisible()) continue;
		const animationManager& anim = menu->getAnimationManager();

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
	renderer::getInstance().drawToNextFrame(tex, 0, 0, static_cast<float>(logicalH), static_cast<float>(logicalW));
}
 
void renderManager::renderEntities(game& g, const std::vector<entity*>& cache) {

	const viewPort& view = g.getView();
	const float camX = view.viewPos.getX();
	const float camY = view.viewPos.getY(); 
	  float screenX = 0;
	  float screenY = 0;
	for (auto& e : cache) { 
		animationManager& a = e->getAnimationManager();
		const position pos = e->getCombinedPos();

		screenX = pos.getX() - camX;
		screenY = pos.getY() - camY;
		//		renderer::getInstance().drawToNextFrame(i.tex, screenX, screenY, i.height, i.width);
		renderer::getInstance().drawToNextFrame(a.getCurrentTexture(), screenX, screenY, a.getHeight(), a.getWidth());
	}
} 

void renderManager::renderDialogue(dialogueManager& dlg) {
	activeDialogue aDlg = dlg.getActiveDialogues().back();
	 
	renderer::getInstance().drawToNextFrame(textureManager::getInstance().getFrame("textBubble_idle_0"), aDlg.bubbleRect.x, aDlg.bubbleRect.y, aDlg.bubbleRect.h, aDlg.bubbleRect.w);

	renderer::getInstance().drawToNextFrame(aDlg.textLabel.texture, aDlg.textLabel.pos.getX(), aDlg.textLabel.pos.getY(), aDlg.textLabel.h, aDlg.textLabel.w);

}

void renderManager::renderGame(game& g, menuManager& m) {
	renderCacheManager& cache = g.getRenderCacheManager();
	renderBackground();
	renderEntities(g, cache.getRenderableTiles());
	renderEntities(g, cache.getRenderableEntities());
	renderDialogue(g.getDialogueManager());
	//renderGameMenu(g);
	renderMainMenu(m);
	renderer::getInstance().drawScreen();
} 