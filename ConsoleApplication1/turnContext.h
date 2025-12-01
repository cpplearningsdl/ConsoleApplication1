#pragma once 
#include "event.h"
#include "gamePhaseEnum.h"
#include "characterTypeEnum.h"
#include <vector>
#include <deque>
#include "json.hpp"

class entity;
struct baseEvent;

//ADD TYPE TO JSON!!!!!!
struct turnContext {
	entity* activeCharacter = nullptr;     // who is currently selected / moving (single mover)
	int activeCharacterId = -1;
	CHARACTERTYPEENUM actorType = CHARACTERTYPEENUM::PLAYER;

	int moveDistanceRemaining = 0; 
	int actionsRemaining = 1;
	bool battleAllowed = true;         // true if you can initiate battle right now (not mid-move)
	bool turnFinished = false;         // when both actor and actions are done

	std::deque<std::unique_ptr<baseEvent>> events;
	// Optional bookkeeping
	gamePhase phase = gamePhase::DECISION;
	gamePhase originPhase = gamePhase::DECISION;  

	template<typename T, typename... Args>
	void emitEvent(Args&&... args) {
		events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
};

inline void clearCtx(turnContext& ctx) {
	ctx.activeCharacter = nullptr;
	ctx.activeCharacterId = -1;
	ctx.actorType = CHARACTERTYPEENUM::PLAYER;
	ctx.moveDistanceRemaining = 0;
	ctx.actionsRemaining = 0;
	ctx.battleAllowed = true;
	ctx.turnFinished = false;
	ctx.events.clear();
	ctx.phase = gamePhase::DECISION;
	ctx.originPhase = gamePhase::DECISION;
}
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