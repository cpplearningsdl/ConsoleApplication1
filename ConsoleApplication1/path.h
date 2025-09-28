#pragma once
#include "json.hpp"
#include <vector>
#include "position.h"
#include "movementTypeEnum.h"
#include "logManager.h"

struct movementPath
{
	std::vector<movementTypeEnum> turns;
	position startPos;
	position destination; 

};


inline void addTurnToPath(movementPath& p, movementTypeEnum t) {
	p.turns.push_back(t); 
}
inline movementTypeEnum getNextDirection(movementPath& p) {
	movementTypeEnum np = p.turns.back();
	p.turns.pop_back(); 
	return np;
}
// movementPath JSON
inline void to_json(nlohmann::ordered_json& j, const movementPath& p) {
	std::vector<std::string> turnsStr;
	turnsStr.reserve(p.turns.size());
	for (auto t : p.turns) {
		turnsStr.push_back(movementTypeEnumToString(t));
	}

	j = nlohmann::ordered_json{
		{"turns", turnsStr},
		{"startPos", p.startPos},
		{"destination", p.destination}
	};
}

inline void from_json(const nlohmann::ordered_json& j, movementPath& p) {
	std::vector<std::string> turnsStr;
	j.at("turns").get_to(turnsStr);

	p.turns.clear();
	p.turns.reserve(turnsStr.size());
	for (auto& s : turnsStr) {
		p.turns.push_back(stringToMovementTypeEnum(s));
	}

	j.at("startPos").get_to(p.startPos);
	j.at("destination").get_to(p.destination);
}