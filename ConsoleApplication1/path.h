#pragma once
#include "json.hpp"
#include <vector>
#include "position.h"
#include "movementTypeEnum.h"
#include "logManager.h"

struct movementPath
{
	std::vector<position>wayPoints;
	position startPos;
	position destination; 

	movementPath() = default;
	movementPath(std::vector<position> points, position start, position dest) :
		wayPoints(points), startPos(start), destination(dest) {};
};

inline void addToWayPoints(movementPath& p, position pos) {
	p.wayPoints.push_back(pos);
}
inline float getNextDestinationX(movementPath&p) {
	return p.wayPoints.back().getX(); 
}
inline float getNextDestinationY(movementPath& p) {
	return p.wayPoints.back().getY(); 
}

inline position getNextWaypoint(movementPath& p) { return { getNextDestinationX(p), getNextDestinationY(p) }; }

inline void popWayPoint(movementPath& p) {
	if (p.wayPoints.size() > 0) {
		p.wayPoints.pop_back();
	}
}

 
inline bool pathFinished(movementPath& p) { return p.wayPoints.size() == 0; }

// movementPath JSON
inline void to_json(nlohmann::ordered_json& j, const movementPath& p) {
	j = nlohmann::ordered_json{
		{"wayPoints", p.wayPoints},
		{"startPos", p.startPos},
		{"destination", p.destination}
	};
}

inline void from_json(const nlohmann::ordered_json& j, movementPath& p) {
	if (j.contains("waypoints")) {
		j.at("wayPoints").get_to(p.wayPoints);
	}
	else { p.wayPoints.clear(); }

	j.at("startPos").get_to(p.startPos);
	j.at("destination").get_to(p.destination);
}