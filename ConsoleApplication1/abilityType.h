#pragma once
#include <string>
#include <algorithm>
enum class abilityType : int {
	NONE,
	ACTIVEBOTH,
	BATTLEONLY,
	FIELDONLY,
	PASSIVEBATTLEONLY,
	PASSIVEFIELDONLY,
	PASSIVEBOTH

};

inline const char* abilityTypeToString(abilityType t) {
	switch (t) {
	case abilityType::NONE: return "NONE"; 
	case abilityType::ACTIVEBOTH: return "ACTIVEBOTH";
	case abilityType::BATTLEONLY: return "BATTLEONLY";
	case abilityType::FIELDONLY: return "FIELDONLY";
	case abilityType::PASSIVEBATTLEONLY: return "PASSIVEBATTLEONLY";
	case abilityType::PASSIVEFIELDONLY: return "PASSIVEFIELDONLY";
	case abilityType::PASSIVEBOTH: return "PASSIVEBOTH";
	default: return "NONE";
	}
}

inline abilityType stringToAbilityType(const std::string& s) {
	std::string upper = s;
	std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
	if (upper == "NONE") return abilityType::NONE; 
	if (upper == "ACTIVEBOTH") return abilityType::ACTIVEBOTH;
	if (upper == "BATTLEONLY") return abilityType::BATTLEONLY;
	if (upper == "FIELDONLY") return abilityType::FIELDONLY;
	if (upper == "PASSIVEBATTLEONLY") return abilityType::PASSIVEBATTLEONLY;
	if (upper == "PASSIVEFIELDONLY") return abilityType::PASSIVEFIELDONLY;
	if (upper == "PASSIVEBOTH") return abilityType::PASSIVEBOTH;
	return abilityType::NONE;
}