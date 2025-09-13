#pragma once
#include <string>
#include <algorithm>
#include <cstddef>
enum class movementTypeEnum : int {
	missing,
	north,
	east,
	south,
	west,
	movementenumcount
};

inline movementTypeEnum movementTypeEnumCount() {return movementTypeEnum::movementenumcount;}

inline const char* movementTypeEnumToString(movementTypeEnum e) {
	switch (e) {
	case movementTypeEnum::north:         return "north";
	case movementTypeEnum::east:           return "east";
	case movementTypeEnum::south:           return "south";
	case movementTypeEnum::west:           return "west"; 
	default:                        return "missing";
	}
}

inline movementTypeEnum stringToMovementTypeEnum(const std::string& s) {
	std::string upper = s;
	std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
	if (upper == "MISSING")			return movementTypeEnum::missing;
	if (upper == "NORTH") return movementTypeEnum::north;
	if (upper == "EAST") return movementTypeEnum::east;
	if (upper == "SOUTH") return movementTypeEnum::south;
	if (upper == "WEST") return movementTypeEnum::west;
	return movementTypeEnum::missing; // fallback
}