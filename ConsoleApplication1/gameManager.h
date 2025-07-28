#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <memory>
#include "game.h"   

class gameManager {
public:
	static gameManager& getInstance();

	void newGame();
	void endGame();
	void processGame(); 

private:
	gameManager() = default;
	~gameManager() = default;

	gameManager(const gameManager&) = delete;
	gameManager& operator=(const gameManager&) = delete;

	std::unique_ptr<game> currentGame;
};

#endif
