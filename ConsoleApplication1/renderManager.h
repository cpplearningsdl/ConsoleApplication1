#pragma once
#include <vector>
#include "logManager.h"
#include "game.h"
#include "menuManager.h"
#include "menu.h"
#include "renderer.h"

class renderManager
{
private:

public:
	void renderGame(game& g, menuManager& m);
	void renderMainMenu(menuManager& m);
	void renderBackground();
	void renderEntities(game& g, const std::vector<entity*>& cache); 
	void renderDialogue(dialogueManager& dlg);
};

