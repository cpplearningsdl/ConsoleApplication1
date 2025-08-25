#include "ability.h"

ability::ability(const std::string& name, int maxUses, int basePower, int currentPower)
	: name(std::move(name)), uses(maxUses), basePower(basePower), currentPower(currentPower)
{
}
 
const std::string& ability::getName() const { return name; } 
int ability::getBasePower() const { return basePower; }
int ability::getCurrentPower() const { return currentPower; }
abilityType ability::getAbilityType() const { return abilityType; }
 
void ability::increaseCurrentPower(int amount) {
	currentPower = currentPower + amount;
	if (currentPower < 0) {
		currentPower = 0;
	} 
}

void ability::setCurrentPower(int amount) {
	currentPower = amount;
	if (currentPower < 0) { currentPower = 0; }
}

void ability::reset() {
	currentPower = basePower;
	uses.setCurrent = uses.getMax;
}
 
// Example effect execution (placeholder)
void  ability::executeEffect(gameContext& ctx) {
	// Here you would implement the actual effect of the ability.
	// For example, damage calculation, healing, buffs, debuffs, etc.
	// This is just a placeholder for now.
}
