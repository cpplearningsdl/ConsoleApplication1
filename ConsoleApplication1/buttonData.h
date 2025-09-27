#pragma once
#include "buttonEnums.h"
#include "logManager.h"
#include "position.h"
#include "dimensions.h"

#include <SDL3/SDL.h>

struct buttonsActionData {
	int id;
	//SDL_Texture* tex;
	bool clicked = false;
	butEnum action;
	int actionIndex1 = -1;
	int actionIndex2 = -1;
	int value1 = 0;
	int value2 = 0;
};


struct buttonsMenuData {
	int id;
	position pos;
	dimensions size;
	bool render;
	std::string name;
};


inline void buttonSpillGuts(buttonsActionData bd) {
	logManager::logThis("Button Spills Guts:");
	logManager::logThis("id: ", bd.id);
	logManager::logThis("clicked: ", bd.clicked);
	logManager::logThis("Action: ", butDataToString(bd.action));
	logManager::logThis("Index1: ", bd.actionIndex1);
	logManager::logThis("Index2: ", bd.actionIndex2);
}

inline void buttonSpillGuts(buttonsMenuData bd) {
	logManager::logThis("Button Spills Guts:");
	logManager::logThis("id: ", bd.id);
	logManager::logThis("pos: ", bd.pos.getX() + " " + bd.pos.getY());
	logManager::logThis("size: ", bd.size.getH() + " " + bd.size.getW());
	logManager::logThis("render: ", bd.render);
	logManager::logThis("name: ", bd.name);
}