#pragma once
#include <memory>
#include "game.h"   
#include "renderManager.h"
#include "menuManager.h"
#include "mainMenu.h"
#include "inputManager.h"
#include "abilityFactory.h"
#include "abilityFileLoader.h" 
#include "gameStateEnum.h"


class gameManager {
public:
	static gameManager& getInstance();

	void newGame();
	void endGame();
	void loadDefaultAssets();
	void processGame(); 
	void processMenu(inputManager& input);
	void setState(gameStateEnum nState) { state = nState; }
	gameStateEnum getState() { return state; }
	menuManager& getPauseMenu() { return thePauseMenu; }
	void init() { theStartMenu.openMenu(std::make_unique<mainMenu>()); }
	void render(); 
private:
	gameManager() = default;
	~gameManager() = default;

	gameManager(const gameManager&) = delete;
	gameManager& operator=(const gameManager&) = delete;

	std::unique_ptr<game> currentGame;
	renderManager renderHandler;
	menuManager thePauseMenu;
	menuManager theStartMenu; 
	gameStateEnum state;

};
 
