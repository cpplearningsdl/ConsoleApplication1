#pragma once
#include <vector>
#include <memory>
#include <string>
#include "json.hpp"
#include "abilityFactory.h"
#include "abilityFileLoader.h"
#include "ability.h"
#include "heal.h"

class abilities {
public: 
	abilities() = default;
	abilities(const abilities& other) {
		for (const auto& ab : other.abilityContainer) {
			if (ab) {
				abilityContainer.push_back(ab->clone()); // clone each ability
			}
		}
	}
	 
	abilities& operator=(const abilities& other) {
		if (this != &other) {
			abilityContainer.clear();
			for (const auto& ab : other.abilityContainer) {
				if (ab) {
					abilityContainer.push_back(ab->clone());
				}
			}
		}
		return *this;
	}
	void addAbility(const ability& masterAbility);
	void addAbility(std::unique_ptr<ability> newAbility);
	void removeAbility(const std::string& name);
	 
	ability* getAbility(const std::string& name);
	 
	const std::vector<std::unique_ptr<ability>>& getAll() const;

	nlohmann::ordered_json to_Json(const abilities& abContainer);
private:
	std::vector<std::unique_ptr<ability>> abilityContainer; // polymorphic storage
};
