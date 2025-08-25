#include "abilities.h"
#include <algorithm>

void abilities::addAbility(const ability& masterAbility) {
	abilities.push_back(masterAbility.clone()); // deep copy via clone()
}

void abilities::removeAbility(const std::string& name) {
	abilities.erase(
		std::remove_if(abilities.begin(), abilities.end(),
			[&](const std::unique_ptr<ability>& a) { return a->getName() == name; }),
		abilities.end()
	);
}

ability* abilities::getAbility(const std::string& name) {
	for (auto& a : abilities) {
		if (a->getName() == name) {
			return a.get();
		}
	}
	return nullptr;
}

const std::vector<std::unique_ptr<ability>>& abilities::getAll() const {
	return abilities;
}
