#pragma once

enum class movementTypeEnum : int {
	north,
	east,
	south,
	west,
	count 
};

inline movementTypeEnum count() { return movementTypeEnum::count; }