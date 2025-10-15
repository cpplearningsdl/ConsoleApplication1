#pragma once
#include "json.hpp"
#include <vector>
#include "position.h"
#include "movementTypeEnum.h"
#include "logManager.h"

struct movementPath
{
	std::vector<movementTypeEnum> turns;
	std::vector<position>wayPoints;
	position startPos;
	position destination; 

};


inline void addTurnToPath(movementPath& p, movementTypeEnum t) {
	p.turns.push_back(t); 
}
inline void addToWayPoints(movementPath& p, position pos) {
	p.wayPoints.push_back(pos);
}
inline float getNextDestinationX(movementPath&p) {
	float nX = p.wayPoints.back().getX(); 
	return nX;
}
inline float getNextDestinationY(movementPath& p) {
	float nY = p.wayPoints.back().getY();
	return nY;
}
inline void popNextWayPoint(movementPath& p) { p.wayPoints.pop_back(); }

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
		{"wayPoints", p.wayPoints},
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

	if (j.contains("waypoints")) {
		j.at("wayPoints").get_to(p.wayPoints);
	}
	else { p.wayPoints.clear(); }

	j.at("startPos").get_to(p.startPos);
	j.at("destination").get_to(p.destination);
}