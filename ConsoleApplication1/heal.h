#pragma once
#include "ability.h"
#include "statsContainer.h"
#include "uses.h"
#include "json.hpp"

using json = nlohmann::ordered_json;

class heal : public ability {
public: 
	heal() = default;

	std::unique_ptr<ability> clone() const override {
		return std::make_unique<heal>(*this);
	}

	void executeEffect(gameContext& ctx) override {
		if (usesLeft.canUse()) {
			auto& timesUsedStat = stats.get(statEnum::TIMESUSED);
			timesUsedStat.setCurrent(timesUsedStat.getCurrent() + 1);
			usesLeft.useOne();
		}
	}
	 
	statsContainer& getStats() { return stats; }
	const statsContainer& getStats() const { return stats; }

	uses& getUsesLeft() { return usesLeft; }
	const uses& getUsesLeft() const { return usesLeft; }


	json to_Json() const override {
		json j;
		j["name"] = getName();
		j["type"] = abilityTypeToString(type);
		j["stats"] = stats;  
		j["usesLeft"] = usesLeft;  
		return j;
	}
	void from_Json(const nlohmann::ordered_json& j) override {
		if (j.contains("name")) { 
			const_cast<std::string&>(getName()) = j.at("name").get<std::string>();
		}

		if (j.contains("type")) {
			std::string typeStr = j.at("type").get<std::string>();
			setAbilityType(stringToAbilityType(typeStr));
		}

		if (j.contains("stats")) {
			getStats() = j.at("stats").get<statsContainer>();
		}

		if (j.contains("usesLeft")) {
			getUsesLeft() = j.at("usesLeft").get<uses>();
		}
	}

private:
	statsContainer stats;
	uses usesLeft;
};

