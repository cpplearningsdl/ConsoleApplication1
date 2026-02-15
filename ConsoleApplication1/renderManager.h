#pragma once
#include <vector>
#include "logManager.h"
#include "game.h"
#include "menuManager.h"
#include "menu.h"
#include "renderer.h"
#include "textureManager.h"
#include "fireLineBatch.h"
#include "particleBatch.h"

class position;
class dimensions;


class renderManager
{
private:
	renderer& rendRef = { renderer::getInstance() };
	textureManager& textureManagerRef = { textureManager::getInstance() };
public:
	void renderGame(game& g, menuManager& m);
	void renderLights(game& g);
	void renderEntityLights(game& g, const std::vector<entity*>& cache);
	void renderMainMenu(menuManager& m);
	void renderBackground();
	void renderEntities(game& g, const std::vector<entity*>& cache); 
	void renderDialogue(game& g, dialogueManager& dlg);
	void renderLightning(game& g);
	void renderFire(game& g);
	void renderParticles(game& g);
	void renderRain(game& g);
	void renderLineBatch(fireLineBatch& lineBatch);
	void renderMonocolorLineBatch(fireLineBatch& lineBatch);
	void renderPointBatch(particleBatch& pointBatch);
	void renderParticleBatchRects(particleBatch& batch);
};

