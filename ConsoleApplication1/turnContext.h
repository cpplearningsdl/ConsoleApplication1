#pragma once
#include "entity.h"
#include "GameEvent.h"
#include "gamePhaseEnum.h"
#include "characterTypeEnum.h"
#include <vector>
#include "json.hpp"



struct turnContext {
	entity* activeCharacter = nullptr;     // who is currently selected / moving (single mover)
	int activeCharacterId = -1;
	CHARACTERTYPEENUM actorType = CHARACTERTYPEENUM::PLAYER;

	int moveDistanceRemaining = 0;       // movement budget for this turn (tiles)
	int actionsRemaining = 1;
	bool battleAllowed = true;         // true if you can initiate battle right now (not mid-move)
	bool turnFinished = false;         // when both actor and actions are done

	std::vector<gameEvent> events;
	// Optional bookkeeping
	gamePhase originPhase = gamePhase::DECISION;  
};

inline void to_Json(nlohmann::ordered_json& j, const turnContext& t) {
	j = nlohmann::ordered_json{
		{ "activeCharacterId", t.activeCharacterId },
		{ "actorType", characterTypeEnumToString(t.actorType) },
		{ "moveDistanceRemaining", t.moveDistanceRemaining },
		{ "actionsRemaining", t.actionsRemaining },
		{ "battleAllowed", t.battleAllowed },
		{ "turnFinished", t.turnFinished },
		{ "originPhase", gamePhaseEnumToString(t.originPhase) }
	}; 
}

inline void from_Json(const nlohmann::ordered_json& j, turnContext& t) {
	t.activeCharacterId = j.value("activeCharacterId", -1);
	t.actorType = stringToCharacterTypeEnum(j.value("actorType", ""));
	t.moveDistanceRemaining = j.value("moveDistanceRemaining", 0);
	t.actionsRemaining = j.value("actionsRemaining", 1);
	t.battleAllowed = j.value("battleAllowed", true);
	t.turnFinished = j.value("turnFinished", false);
	t.originPhase = stringToGamePhaseEnum(j.value("originPhase", ""));
	t.activeCharacter = nullptr; // will be resolved at runtime using activeCharacterId
}