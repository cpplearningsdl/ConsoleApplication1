#pragma once
#include "json.hpp"

enum class gamePhase {
	STARTTURN,
	DECISION,
	MENU,
	MOVEMENT,
	BATTLE,
	CUTSCENE,
	OTHER,
	MISSING
}; 

inline std::string gamePhaseEnumToString(gamePhase p) {
	switch (p) {
		case gamePhase::STARTTURN: return "STARTTURN";
		case gamePhase::DECISION: return "DECISION";
		case gamePhase::MENU: return "MENU";
		case gamePhase::MOVEMENT: return "MOVEMENT";
		case gamePhase::BATTLE: return "BATTLE";
		case gamePhase::CUTSCENE: return "CUTSCENE";
		case gamePhase::OTHER: return "OTHER";
		case gamePhase::MISSING: return "MISSING";
	} 	
}

inline gamePhase stringToGamePhaseEnum(std::string p) {
	if (p == "STARTTURN") { return gamePhase::STARTTURN; }
	if (p == "DECISION") { return gamePhase::DECISION; }
	if (p == "MENU") { return gamePhase::MENU; }
	if (p == "MOVEMENT") { return gamePhase::MOVEMENT; }
	if (p == "BATTLE") { return gamePhase::BATTLE; }
	if (p == "CUTSCENE") { return gamePhase::CUTSCENE; }
	if (p == "OTHER") { return gamePhase::OTHER; }
	return gamePhase::MISSING;
}

inline void to_json(nlohmann::json& j, const gamePhase& p) {
	j = gamePhaseEnumToString(p);
}

inline void from_json(const nlohmann::json& j, gamePhase& p) {
	if (j.is_string()) {
		p = stringToGamePhaseEnum(j.get<std::string>());
	}
	else {
		p = gamePhase::MISSING;
	}
}