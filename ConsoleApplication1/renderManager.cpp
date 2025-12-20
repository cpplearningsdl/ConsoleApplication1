#include "renderManager.h"
#include "entityRenderInfo.h"
#include "windowSettings.h"
#include "position.h"
#include "dimensions.h"
#include "light.h"


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
void renderManager::renderEntityLights(game& g, const std::vector<entity*>& cache) {
	light L = light({ -1.0f,-1.0f }, 128.0f, 0.6f, { 2, 255, 2, 255 });

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
		rendRef.drawLight(screenX + 64, screenY + 64, L.radius, L.color, L.intensity);
	}
}

void renderManager::renderDialogue(game& g, dialogueManager& dlg) {
	if (dlg.getActiveDialogues().empty()) { return; }
	//GETWIDTHFROMBUBBLE TO PASS TO GETTEXTBUBBLESCREENPOS
	activeDialogue aDlg = dlg.getActiveDialogues().back(); 
	rendRef.drawToNextFrame(textureManager::getInstance().getFrame(aDlg.bubbleTextureKey), aDlg.textBubblePos.getX(), aDlg.textBubblePos.getY(), aDlg.textBubbleSize.getH(), aDlg.textBubbleSize.getW());

	rendRef.drawToNextFrame(aDlg.textLabel.texture, aDlg.textBubblePos.getX() + aDlg.textLabel.posOffset.getX(), aDlg.textBubblePos.getY() + aDlg.textLabel.posOffset.getY(), aDlg.textLabel.h, aDlg.textLabel.w);
 
}

void renderManager::renderLights(game& g) {
	for (auto& L : g.getLightManager().getLights()) {
		// adjust for camera
		float screenX = L.pos.getX() - g.getView().viewPos.getX();
		float screenY = L.pos.getY() - g.getView().viewPos.getY();
		rendRef.drawLight(screenX, screenY, L.radius, L.color, L.intensity);
	}
}

void renderManager::renderLightning(game& g) { 
	for (auto& s : g.getEffectsManager().getLightningManager().getStrikes()) {
		for (const auto& seg : s.segments) {
			const auto& a = s.nodes[seg.a];
			const auto& b = s.nodes[seg.b];

			SDL_Color c{
				Uint8(220 * s.intensity),
				Uint8(235 * s.intensity),
				Uint8(255 * s.intensity),
				Uint8(255)
			};

			SDL_SetRenderDrawColor(rendRef.getSDLRenderer(), c.r, c.g, c.b, c.a);
			SDL_RenderLine(
				rendRef.getSDLRenderer(),
				a.basePos.x + a.offset.x,
				a.basePos.y + a.offset.y,
				b.basePos.x + b.offset.x,
				b.basePos.y + b.offset.y
			);
		}
	}
}

void renderManager::renderGame(game& g, menuManager& m) {
	renderCacheManager& cache = g.getRenderCacheManager(); 
	renderBackground();
	renderEntities(g, cache.getRenderableTiles());
	rendRef.drawAmbientDarkness(180);
	renderEntities(g, cache.getRenderableEntities());
	renderEntityLights(g, cache.getRenderableEntities());
	renderLights(g);
	renderLightning(g);


	renderDialogue(g, g.getDialogueManager());
	
	//renderGameMenu(g);
	renderMainMenu(m);
	rendRef.drawScreen();
} 

