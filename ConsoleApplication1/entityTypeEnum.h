#pragma once
enum ENTITYTYPEENUM : int { 
	MISSING,
	TILE,
	ENTITY

};

// Convert enum to string using switch
inline std::string entityTypeToString(ENTITYTYPEENUM type) {
	switch (type) {
	case TILE:   return "TILE";
	case ENTITY: return "ENTITY";
	default:     return "MISSING";
	}
}

// Convert string to enum using if/else
inline ENTITYTYPEENUM entityTypeFromString(const std::string& str) {
	if (str == "MISSING") return MISSING;
	if (str == "TILE")   return TILE; 
	return ENTITY; // default fallback
}