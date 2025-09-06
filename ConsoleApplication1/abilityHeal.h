#pragma once
#include "ability.h"
#include "statsContainer.h"
#include "uses.h"
#include "json.hpp"

using json = nlohmann::json;

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

	// Accessors
	statsContainer& getStats() { return stats; }
	const statsContainer& getStats() const { return stats; }

	uses& getUsesLeft() { return usesLeft; }
	const uses& getUsesLeft() const { return usesLeft; }

	// Serialize this ability into JSON
	json toJson() const {
		json j;
		j["name"] = getName();
		j["type"] = abilityTypeToString(type);
		j["stats"] = stats;  
		j["usesLeft"] = usesLeft;  
		return j;
	}
	inline void from_json(const nlohmann::json& j, heal& h) {
		if (j.contains("name")) { 
			const_cast<std::string&>(h.getName()) = j.at("name").get<std::string>();
		}

		if (j.contains("type")) {
			std::string typeStr = j.at("type").get<std::string>();
			h.setAbilityType(stringToAbilityType(typeStr));
		}

		if (j.contains("stats")) {
			h.getStats() = j.at("stats").get<statsContainer>();
		}

		if (j.contains("usesLeft")) {
			h.getUsesLeft() = j.at("usesLeft").get<uses>();
		}
	}

private:
	statsContainer stats;
	uses usesLeft;
};

