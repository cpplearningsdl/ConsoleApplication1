#include "gameManager.h"
#include "game.h"

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
		currentGame->render();
	}
}
