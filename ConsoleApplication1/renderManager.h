#pragma once
#include <vector>
#include "logManager.h"
#include "game.h"
#include "menuManager.h"
#include "menu.h"
#include "renderer.h"
#include "textureManager.h"

class position;
class dimensions;

class renderManager
{
private:
	renderer& rendRef = { renderer::getInstance() };
	textureManager& textureManagerRef = { textureManager::getInstance() };
public:
	void renderGame(game& g, menuManager& m);
	void renderMainMenu(menuManager& m);
	void renderBackground();
	void renderEntities(game& g, const std::vector<entity*>& cache); 
	void renderDialogue(game& g, dialogueManager& dlg);
};

