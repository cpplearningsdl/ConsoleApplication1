#include "abilities.h"
#include <algorithm>

void Abilities::addAbility(const ability& masterAbility) {
	abilities.push_back(masterAbility.clone()); // deep copy via clone()
}

void Abilities::removeAbility(const std::string& name) {
	abilities.erase(
		std::remove_if(abilities.begin(), abilities.end(),
			[&](const std::unique_ptr<ability>& a) { return a->getName() == name; }),
		abilities.end()
	);
}

ability* Abilities::getAbility(const std::string& name) {
	for (auto& a : abilities) {
		if (a->getName() == name) {
			return a.get();
		}
	}
	return nullptr;
}

const std::vector<std::unique_ptr<ability>>& Abilities::getAll() const {
	return abilities;
}
