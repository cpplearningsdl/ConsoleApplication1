#pragma once
#include <memory>
#include "game.h"   
#include "renderManager.h"
#include "abilityFactory.h"
#include "abilityFileLoader.h" 

class gameManager {
public:
	static gameManager& getInstance();

	void newGame();
	void endGame();
	void loadDefaultAssets();
	void processGame(); 
	void render(); 
private:
	gameManager() = default;
	~gameManager() = default;

	gameManager(const gameManager&) = delete;
	gameManager& operator=(const gameManager&) = delete;

	std::unique_ptr<game> currentGame;
	renderManager renderHandler;
};
 
