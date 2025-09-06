#pragma once
#include <cstddef>

enum class statEnum : size_t {
	MISSINGTYPE,
	LEVEL,
	EXPERIENCE,
	EXPERIENCENEEDED,
	HP,
	MP, 
	MIND,
	INTELLIGENCE,
	ATTACK,
	DEFENSE,
	ACCURACY,
	SPEED,
	AGILITY,
	LUCK,
	GROWTH,
	TIMESUSED,
	COUNT
};

inline statEnum count() { return statEnum::COUNT; }


inline const char* statEnumToString(statEnum e) {
	switch (e) {
	case statEnum::MISSINGTYPE:         return "MISSINGTYPE";
	case statEnum::LEVEL:           return "LEVEL";
	case statEnum::EXPERIENCE:      return "EXPERIENCE";
	case statEnum::EXPERIENCENEEDED:return "EXPERIENCENEEDED";
	case statEnum::HP:              return "HP";
	case statEnum::MP:              return "MP";
	case statEnum::MIND:            return "MIND";
	case statEnum::INTELLIGENCE:    return "INTELLIGENCE";
	case statEnum::ATTACK:          return "ATTACK";
	case statEnum::DEFENSE:         return "DEFENSE";
	case statEnum::ACCURACY:		return "ACCURACY";
	case statEnum::SPEED:           return "SPEED";
	case statEnum::AGILITY:         return "AGILITY";
	case statEnum::LUCK:            return "LUCK";
	case statEnum::GROWTH:          return "GROWTH";
	case statEnum::TIMESUSED:		return "TIMESUSED";
	case statEnum::COUNT:           return "COUNT";
	default:                        return "MISSINGTYPE";
	}
}
 
inline statEnum stringToStatEnum(const std::string& s) {
	std::string upper = s;
	std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
	if (upper == "MISSINGTYPE")			return statEnum::MISSINGTYPE;
	if (upper == "LEVEL")				return statEnum::LEVEL;
	if (upper == "EXPERIENCE")			 return statEnum::EXPERIENCE;
	if (upper == "EXPERIENCENEEDED")	return statEnum::EXPERIENCENEEDED;
	if (upper == "HP")					 return statEnum::HP;
	if (upper == "MP")					 return statEnum::MP;
	if (upper == "MIND")				 return statEnum::MIND;
	if (upper == "INTELLIGENCE")		 return statEnum::INTELLIGENCE;
	if (upper == "ATTACK")				return statEnum::ATTACK;
	if (upper == "DEFENSE")				 return statEnum::DEFENSE;
	if (upper == "ACCURACY")			return statEnum::ACCURACY;
	if (upper == "SPEED")				 return statEnum::SPEED;
	if (upper == "AGILITY")				 return statEnum::AGILITY;
	if (upper == "LUCK")				return statEnum::LUCK;
	if (upper == "GROWTH")				return statEnum::GROWTH;
	if (upper == "TIMESUSED")			return statEnum::TIMESUSED;
	if (upper == "COUNT")				return statEnum::COUNT;
	return statEnum::MISSINGTYPE; // fallback
}