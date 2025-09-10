#include "abilities.h"
#include <algorithm>
#include "logManager.h"

void abilities::addAbility(const ability& masterAbility) {
	abilityContainer.push_back(masterAbility.clone()); 
}
void abilities::addAbility(std::unique_ptr<ability> newAbility) {
	if (newAbility) {
		abilityContainer.push_back(std::move(newAbility));
	}
	else {
		logManager::logThis("Failed to load ability ptr from factory");
	}
}
void abilities::removeAbility(const std::string& name) {
	abilityContainer.erase(
		std::remove_if(abilityContainer.begin(), abilityContainer.end(),
			[&](const std::unique_ptr<ability>& a) {
		return a->getName() == name;
	}),
		abilityContainer.end()
		);
}

ability* abilities::getAbility(const std::string& name) {
	for (auto& a : abilityContainer) {
		if (a->getName() == name) {
			return a.get();
		}
	}
	return nullptr;
}

const std::vector<std::unique_ptr<ability>>& abilities::getAll() const {
	return abilityContainer;
}

nlohmann::ordered_json abilities::to_Json(const abilities& abContainer) {
	json jArray = json::array();

	for (const auto& ab : abContainer.getAll()) {
		if (ab) {
			jArray.push_back(ab->to_Json()); 
		}
	}

	return jArray;
}