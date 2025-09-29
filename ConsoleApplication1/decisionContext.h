#pragma once
#include "entity.h"
#include "ability.h"
#include "position.h"
#include "item.h"

enum class decisionTypeEnum {NONE, MOVEMENT, ABILITY, ITEM,};

struct decisionContext {
	decisionTypeEnum type;
	entity decisionMakingCharacter;
	bool active;
	bool finalized = false;
	virtual ~decisionContext() = default;
};

struct movementDecision : decisionContext {
	std::vector<position> points;
};

struct attackDecision : decisionContext {
	std::vector<entity> targets;
};

struct areaDecision : decisionContext {
	std::vector<position> affectedTiles;
};
  