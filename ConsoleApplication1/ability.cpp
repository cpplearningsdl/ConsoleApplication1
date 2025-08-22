#include "ability.h"

ability::ability(const std::string& name, int maxUses, int baseDamage)
	: name(name), maxUses(maxUses), baseDamage(baseDamage), remainingUses(maxUses)
{
}

// Getters
const std::string& ability::getName() const { return name; }
int ability::getMaxUses() const { return maxUses; } 
int ability::getRemainingUses() const { return remainingUses; }

// Runtime logic
void ability::addUses(int amount) {

	if (amount > 0 && remainingUses < maxUses) {
		remainingUses = remainingUses + maxUses;
	}
	else if (amount <= 0) {
		remainingUses = remainingUses + amount;
	}
 
}

bool ability::isExhausted() const {
	return remainingUses <= 0;
}


// Example effect execution (placeholder)
void  ability::executeEffect(gameContext& ctx) {
	// Here you would implement the actual effect of the ability.
	// For example, damage calculation, healing, buffs, debuffs, etc.
	// This is just a placeholder for now.
}
