#pragma once
#include <string>

enum class CHARACTERTYPEENUM {
	PLAYER,
	AI
};

inline std::string characterTypeEnumToString(CHARACTERTYPEENUM t) {
	switch (t) {
		case CHARACTERTYPEENUM::PLAYER: return "PLAYER";
		case CHARACTERTYPEENUM::AI: return "AI";
	}
}

inline CHARACTERTYPEENUM stringToCharacterTypeEnum(std::string t) {
	if (t == "PLAYER") { return CHARACTERTYPEENUM::PLAYER; }
	if (t == "AI") { return CHARACTERTYPEENUM::AI; }
}