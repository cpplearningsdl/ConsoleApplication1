#include "ability.h" 

ability::ability() 
{

}
 
const std::string& ability::getName() const { return name; }  
abilityType ability::getAbilityType() const { return type; }
void ability::setAbilityType(abilityType  newType) { type = newType;  }
 
// Example effect execution (placeholder)
void  ability::executeEffect(gameContext& ctx) {
	// Here you would implement the actual effect of the ability.
	// For example, damage calculation, healing, buffs, debuffs, etc.
	// This is just a placeholder for now.
}
