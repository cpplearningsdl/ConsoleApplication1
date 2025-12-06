#include "renderManager.h"
#include "entityRenderInfo.h"
#include "windowSettings.h"


void renderManager::renderMainMenu(menuManager& m) {

	for (const auto& menu : m.getMenus()) {
		
		if (!menu->isVisible()) continue;
		const animationManager& anim = menu->getAnimationManager();

		const entityRenderInfo& menuInfo = menu->getEntityRenderInfo();
		rendRef.drawToNextFrame( menuInfo.tex, menuInfo.pos.getX(), menuInfo.pos.getY(), menuInfo.height, menuInfo.width );
		 
		for (const auto& button : menu->getButtons()) {
			const entityRenderInfo& btnInfo = button.getEntityRenderInfo();
			rendRef.drawToNextFrame( btnInfo.tex,	btnInfo.pos.getX(),	btnInfo.pos.getY(), btnInfo.height, btnInfo.width	);
		}
	} 
}

void renderManager::renderBackground() {
	SDL_Texture* tex = textureManager::getInstance().getFrame("background_idle_0"); 
	rendRef.drawToNextFrame(tex, 0, 0, static_cast<float>(logicalH), static_cast<float>(logicalW));
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
		rendRef.drawToNextFrame(a.getCurrentTexture(), screenX, screenY, a.getHeight(), a.getWidth());
	}
} 

void renderManager::renderDialogue(game& g, dialogueManager& dlg) {
	if (dlg.getActiveDialogues().empty()) { return; }

	activeDialogue aDlg = dlg.getActiveDialogues().back();
	position bubblePos = getTextBubbleScreenPos(aDlg.textBubblePos, g.getView().viewPos, logicalW, logicalH, 128.0f, 15.0f);
	rendRef.drawToNextFrame(textureManager::getInstance().getFrame(aDlg.bubbleTextureKey), bubblePos.getX(), bubblePos.getY(), aDlg.textBubbleSize.getH(), aDlg.textBubbleSize.getW());

	rendRef.drawToNextFrame(aDlg.textLabel.texture, bubblePos.getX() + aDlg.textLabel.posOffset.getX(), bubblePos.getY() + aDlg.textLabel.posOffset.getY(), aDlg.textLabel.h, aDlg.textLabel.w);
 
}

void renderManager::renderGame(game& g, menuManager& m) {
	renderCacheManager& cache = g.getRenderCacheManager();
	renderBackground();
	renderEntities(g, cache.getRenderableTiles());
	renderEntities(g, cache.getRenderableEntities());
	renderDialogue(g, g.getDialogueManager());
	//renderGameMenu(g);
	renderMainMenu(m);
	rendRef.drawScreen();
} 


position renderManager::getTextBubbleScreenPos(const position& worldPos, const position& cameraPos,	int screenWidth, int screenHeight, float portraitSize, float buffer){
	// Convert entity world ? screen
	float screenX = worldPos.getX() - cameraPos.getX();
	float screenY = worldPos.getY() - cameraPos.getY();

	// Determine quadrants relative to screen center
	bool left = (screenX < screenWidth * 0.5f);
	bool top = (screenY < screenHeight * 0.5f);

	// Base offsets
	//NEED TO ACCOUNT FOR BUBBLE SIZE!!!!
	float horiz = portraitSize + buffer;
	float vert = portraitSize + buffer;

	// Compute final bubble screen position
	position bubblePos = { screenX, screenY };

	// Horizontal
	if (left)
		bubblePos.setX(bubblePos.getX() + horiz);
	else
		bubblePos.setX(bubblePos.getX() - horiz);

	// Vertical
	if (top)
		bubblePos.setY(bubblePos.getY() + (vert * 0.5f));
	else
		bubblePos.setY(bubblePos.getY() - (vert * 0.5f));

	return bubblePos;
}
