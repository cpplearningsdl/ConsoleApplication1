#include "gameManager.h"
#include "game.h" 
#include "abilityFactory.h"
#include "abilityFileLoader.h" 
#include "entityIncludes.h"
#include "renderer.h"
#include "renderManager.h"
#include "inputManager.h"
#include "menuManager.h"

gameManager& gameManager::getInstance() {
	static gameManager instance;
	return instance;
}

void gameManager::newGame() {
	setState(gameStateEnum::PLAYING);
	currentGame = std::make_unique<game>();
}

void gameManager::endGame() {
	currentGame.reset();  
}

void gameManager::processGame() {
	inputManager& input = inputManager::getInstance();
	processMenu(input);

	if (currentGame) {
		if (getState() == gameStateEnum::PLAYING) {
			currentGame->update();
		}
		render();
	}
}

void gameManager::render() {
	renderHandler.renderGame(*currentGame, mainMenu); 
}

void gameManager::processMenu(inputManager& input) {
	if (getState() == gameStateEnum::PLAYING) {
		if (input.wasKeyReleased(SDL_SCANCODE_ESCAPE)) {
			setState(gameStateEnum::PAUSED); 
			mainMenu.openMenu(std::make_unique<pauseMenu>());
		}
	} else if (getState() == gameStateEnum::PAUSED) { 
		mainMenu.update(input);
		if (input.wasKeyReleased(SDL_SCANCODE_ESCAPE)) {
			setState(gameStateEnum::PLAYING);
			mainMenu.closeTopMenu();
		}
		 else if (mainMenu.getMenus().empty()) {
			setState(gameStateEnum::PLAYING);
		}
	}
 }
 
 
void gameManager::loadDefaultAssets() {
	abilityFactory::getInstance().loadDefaultAbilities();
	entityFactory::getInstance().loadDefaultEntities(); 
}