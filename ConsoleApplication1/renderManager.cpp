#pragma once
#include <SDL3/SDL.h>
#include "renderManager.h"
#include "entityRenderInfo.h"
#include "windowSettings.h"
#include "position.h"
#include "dimensions.h"
#include "light.h"
#include "logManager.h"

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

			float i = std::clamp(s.intensity, 0.0f, 1.5f);
			SDL_Color c{
				Uint8(220 * i),
				Uint8(235 * i),
				Uint8(255 * i),
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
			SDL_RenderLine(
			rendRef.getSDLRenderer(),
				a.basePos.x + a.offset.x +2,
				a.basePos.y + a.offset.y + 2,
				b.basePos.x + b.offset.x + 2,
				b.basePos.y + b.offset.y + 2
			);
		}
	}
}

void renderManager::renderFire(game& g) {
	renderLineBatch(g.getEffectsManager().getFireManager().getFireLineBatch());
	renderPointBatch(g.getEffectsManager().getFireManager().getEmbers());
}

void renderManager::renderParticles(game& g) {
	//renderGroupedPoints(g.getEffectsManager().getParticleManager().getParticleBatch());
	renderParticleBatchRects(g.getEffectsManager().getParticleManager().getParticleBatch());
}

void renderManager::renderPointBatch(particleBatch& b) {
	SDL_Renderer* r = rendRef.getSDLRenderer();

	const size_t count = b.colors.size();
	for (size_t i = 0; i < count; ++i) {
		const SDL_FRect& p = b.rects[i];//move c and p creation out of loop so not creating over and over..
		const SDL_Color& c = b.colors[i];
		SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
		SDL_RenderPoint(r, p.x, p.y);
		SDL_RenderPoint(r, p.x + 1, p.y);
		SDL_RenderPoint(r, p.x, p.y + 1);
		SDL_RenderPoint(r, p.x + 1, p.y + 1);
 
	}
}	
 
void renderManager::renderParticleBatchRects(particleBatch& batch) {
	SDL_Renderer* r = rendRef.getSDLRenderer();
	size_t count = batch.rects.size();
	if (count == 0) return;

	size_t i = 0;

	while (i < count)
	{
		SDL_Color c = batch.colors[i];
		SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);

		uint32_t packed = packColor(c);
		size_t start = i;

		// group consecutive rects with same color
		while (i < count && packColor(batch.colors[i]) == packed)
			++i;

		SDL_RenderRects(r,
			batch.rects.data() + start,
			static_cast<int>(i - start));
	}
}


void renderManager::renderLineBatch(fireLineBatch& lineBatch) {
	if (lineBatch.starts.empty() || lineBatch.ends.empty() || lineBatch.colors.empty()) return;
	 
	const size_t count = lineBatch.starts.size();

	for (size_t i = 0; i < count; ++i) {
		const SDL_FPoint& s = lineBatch.starts[i];
		const SDL_FPoint& e = lineBatch.ends[i];
		const SDL_Color& c = lineBatch.colors[i];

		SDL_SetRenderDrawColor(rendRef.getSDLRenderer(), c.r, c.g, c.b, c.a);

		SDL_RenderLine(
			rendRef.getSDLRenderer(),
			static_cast<int>(s.x),
			static_cast<int>(s.y),
			static_cast<int>(e.x),
			static_cast<int>(e.y)
		);
	}
};

void renderManager::renderGame(game& g, menuManager& m) {
	renderCacheManager& cache = g.getRenderCacheManager(); 
	renderBackground();
	renderEntities(g, cache.getRenderableTiles());
	rendRef.drawAmbientDarkness(180);
	renderEntities(g, cache.getRenderableEntities());
	renderEntityLights(g, cache.getRenderableEntities());
	renderLights(g);
	renderLightning(g); 
	renderFire(g);
	renderParticles(g);
	renderDialogue(g, g.getDialogueManager());
	
	//renderGameMenu(g);
	renderMainMenu(m);
	rendRef.drawScreen();
} 

