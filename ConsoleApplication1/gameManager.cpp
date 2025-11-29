#include "gameManager.h"
#include "game.h" 
#include "abilityFactory.h"
#include "abilityFileLoader.h"  
#include "renderer.h"
#include "renderManager.h"
#include "inputManager.h"
#include "menuManager.h"
#include "fontManager.h"

gameManager& gameManager::getInstance() {
	static gameManager instance;
	return instance;
}

void gameManager::newGame() {
	setState(gameManagerStateEnum::PLAYING);
	currentGame = std::make_unique<game>(); 
}

void gameManager::endGame() {
	currentGame.reset();  
}
 
void gameManager::processGame() {
	inputManager& input = inputManager::getInstance();
	//start menu(when starting game)CLICKING NEW GAME DOESNT START NEW GAME, JUST CLOSES MENU FOR NOW
	if (theStartMenu.hasOpenWindow()) {
		theStartMenu.update(input);
		renderHandler.renderMainMenu(theStartMenu);
		renderer::getInstance().drawScreen();
	}
	else {
		//pause menu, in game
		processMenu(input); 
		if (currentGame) {
			if (getState() == gameManagerStateEnum::PLAYING) {
				currentGame->update(input);
			} 
		}
		render();
	}

}

void gameManager::render() {
	renderHandler.renderGame(*currentGame, thePauseMenu);
}

void gameManager::processMenu(inputManager& input) {
	if (getState() == gameManagerStateEnum::PLAYING) {
		if (input.wasKeyReleased(SDL_SCANCODE_ESCAPE)) {
			setState(gameManagerStateEnum::PAUSED); 
			thePauseMenu.openMenu(std::make_unique<pauseMenu>());
		}
	} else if (getState() == gameManagerStateEnum::PAUSED) { 
		thePauseMenu.update(input);
		if (input.wasKeyReleased(SDL_SCANCODE_ESCAPE)) {
			setState(gameManagerStateEnum::PLAYING);
			thePauseMenu.closeTopMenu();
		}
		 else if (thePauseMenu.getMenus().empty()) {
			setState(gameManagerStateEnum::PLAYING);
		}
	}
 }
 
 
void gameManager::loadDefaultAssets() {
	abilityFactory::getInstance().loadDefaultAbilities();
	entityFactory::getInstance().loadDefaultEntities();
	fontManager::getInstance().loadDefaultFonts();
}