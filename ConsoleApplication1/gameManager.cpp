#include "gameManager.h"
#include "game.h" 
#include "abilityFactory.h"
#include "abilityFileLoader.h" 
#include "entityIncludes.h"
#include "renderer.h"
#include "renderManager.h"
#include "inputManager.h"

gameManager& gameManager::getInstance() {
	static gameManager instance;
	return instance;
}

void gameManager::newGame() {
	currentGame = std::make_unique<game>();
}

void gameManager::endGame() {
	currentGame.reset();  
}

void gameManager::processGame() {
	if (currentGame) {
		currentGame->update(); 
		render();
	}
}
 
void gameManager::render() {
	renderHandler.renderGame(*currentGame); 
}
 
 
void gameManager::loadDefaultAssets() {
	abilityFactory::getInstance().loadDefaultAbilities();
	entityFactory::getInstance().loadDefaultEntities(); 
}