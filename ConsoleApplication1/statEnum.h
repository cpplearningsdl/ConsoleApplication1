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
	SPEED,
	AGILITY,
	LUCK,
	GROWTH,
	COUNT
};

statEnum count() { return statEnum::COUNT; }