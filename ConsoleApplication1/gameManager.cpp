#include "gameManager.h"
#include "game.h" 
#include "abilityFactory.h"
#include "abilityFileLoader.h" 
#include "entityIncludes.h"
#include "renderer.h"
#include "renderManager.h"


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

//void gameManager::render() {
//	renderEntities();
//	renderer::getInstance().drawScreen();
//}
void gameManager::render() {
	renderHandler.renderGame(*currentGame); 
}

void gameManager::renderEntities() {
	std::vector<entity*> renderables = currentGame->getRenderables();
	for (auto& e : renderables) {
		std::string key = e->getAnimationManager().getTextureKey();
		//logManager::logThis("Rendering key: ", key);
		renderer::getInstance().drawToNextFrame(key, 110, 0);
	}
}


 
void gameManager::loadDefaultAssets() {
	abilityFactory::getInstance().loadDefaultAbilities();
	entityFactory::getInstance().loadDefaultEntities(); 
}