#pragma once
#include "buttonEnums.h"
#include "logManager.h"
#include "position.h"
#include "dimensions.h"
#include "json.hpp"
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

inline void to_json(nlohmann::ordered_json& j, const buttonsActionData& b) {
	j = nlohmann::ordered_json{
		{"id", b.id},
		{"clicked", b.clicked},
		{"action", butDataToString(b.action)},  // enum as string
		{"actionIndex1", b.actionIndex1},
		{"actionIndex2", b.actionIndex2},
		{"value1", b.value1},
		{"value2", b.value2}
	};
}
 
inline void from_json(const nlohmann::ordered_json& j, buttonsActionData& b) {
	j.at("id").get_to(b.id);
	j.at("clicked").get_to(b.clicked);

	std::string actionStr;
	j.at("action").get_to(actionStr);
	b.action = stringToButEnum(actionStr); // use your helper

	j.at("actionIndex1").get_to(b.actionIndex1);
	j.at("actionIndex2").get_to(b.actionIndex2);
	j.at("value1").get_to(b.value1);
	j.at("value2").get_to(b.value2);
}
 

inline void buttonSpillGuts(buttonsActionData bd) {
	logManager::logThis("Button Spills Guts:");
	logManager::logThis("id: ", bd.id);
	logManager::logThis("clicked: ", bd.clicked);
	logManager::logThis("Action: ", butDataToString(bd.action));
	logManager::logThis("Index1: ", bd.actionIndex1);
	logManager::logThis("Index2: ", bd.actionIndex2);
}

 