#include "abilities.h"
#include "ability.h"
#include <algorithm>

void Abilities::addAbility(const ability& masterAbility) {
	abilities.push_back(masterAbility); // copy from master
}

void Abilities::removeAbility(const std::string& name) {
	abilities.erase(
		std::remove_if(abilities.begin(), abilities.end(),
			[&](const ability& a) { return a.getName() == name; }),
		abilities.end()
	);
}

ability* Abilities::getAbility(const std::string& name) {
	for (auto& ability : abilities) {
		if (ability.getName() == name) {
			return &ability;
		}
	}
	return nullptr;
}

const std::vector<ability>& Abilities::getAll() const {
	return abilities;
}
