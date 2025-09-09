
#include "entity.h"
#include "json.hpp"
using json = nlohmann::json;

entity::entity() { 
}	

void entity::update() {

}
 
abilities& entity::getAbilities() {
	return abilities;
}

const abilities& entity::getAbilities() const {
	return abilities;
}

void entity::from_Json(const nlohmann::json& j) {
	if (j.contains("name")) {
		setName(j.at("name").get<std::string>());
	}
	if (j.contains("entityId")) {
		setEntityId(j.at("entityId").get<int>());
	}
	if (j.contains("factoryId")) {
		setFactoryId(j.at("factoryId").get<int>());
	}
	if (j.contains("stats")) {
		stats = j.at("stats").get<statsContainer>();
	}
	if (j.contains("abilities")) {
		for (const auto& abName : j["abilities"]) {
			auto ability = abilityFactory::getInstance().create(abName.get<std::string>());
			if (ability) {
				abilities.addAbility(std::move(ability));
			}
		}
	}
}
json entity::to_Json(const entity& e) {
	json j;
	j["entityId"] = e.getId();
	j["factoryId"] = e.getFactoryId();
	j["name"] = e.getName();
	j["stats"] = e.getStats();
	nlohmann::json abilitiesArray = nlohmann::json::array();
	for (const auto& abPtr : e.getAbilities().getAll()) {
		if (abPtr) {
			abilitiesArray.push_back(abPtr->to_Json());  // each subclass implements to_json()
		}
	}
	j["abilities"] = abilitiesArray;
	return j;
}