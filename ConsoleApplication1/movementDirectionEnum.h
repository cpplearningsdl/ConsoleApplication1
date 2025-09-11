#pragma once
#include <string>
enum class movementDirectionEnum {
	north,
	south,
	east,
	west,
	UNKNOWN
};

inline movementDirectionEnum stringToMovementDirection(const std::string& str) {
	if (str == "north") return movementDirectionEnum::north;
	if (str == "south") return movementDirectionEnum::south;
	if (str == "east")  return movementDirectionEnum::east;
	if (str == "west")  return movementDirectionEnum::west;
	return movementDirectionEnum::UNKNOWN;
}

inline std::string movementDirectionToString(movementDirectionEnum type) {
	switch (type) {
	case movementDirectionEnum::north: return "north";
	case movementDirectionEnum::south: return "south";
	case movementDirectionEnum::east:  return "east";
	case movementDirectionEnum::west:  return "west";
	default: return "unknown";
	}
}
