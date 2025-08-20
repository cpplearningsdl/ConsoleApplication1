#include "ability.h"

ability::ability(const std::string& name, int maxUses, int baseDamage)
	: name(name), maxUses(maxUses), baseDamage(baseDamage), remainingUses(maxUses)
{
}

// Getters
const std::string&  ability::getName() const { return name; }
int  ability::getMaxUses() const { return maxUses; }
int  ability::getBaseDamage() const { return baseDamage; }
int  ability::getRemainingUses() const { return remainingUses; }

// Runtime logic
void  ability::decrementUses() {
	if (remainingUses > 0) {
		--remainingUses;
	}
}

bool  ability::isExhausted() const {
	return remainingUses <= 0;
}

// Example effect execution (placeholder)
void  ability::executeEffect(GameContext& ctx) {
	// Here you would implement the actual effect of the ability.
	// For example, damage calculation, healing, buffs, debuffs, etc.
	// This is just a placeholder for now.
}
