#pragma once
#include <unordered_map>
#include "statClass.h"
#include "statEnum.h"
#include "logManager.h"
#include "C:\Users\Keary\source\repos\ConsoleApplication1\ConsoleApplication1\include\json.hpp"

class statsContainer {
private:
	std::unordered_map<statEnum, statClass> statsMap;

public:
	statsContainer() = default;
	 
	void add(statEnum type, const statClass& s) {
		statsMap[type] = s;  
	}
	 
	void add(statEnum type, statClass&& s) {
		statsMap[type] = std::move(s);
	}
	 
	statClass& get(statEnum type) {
		return statsMap.at(type); // throws if type doesn't exist 
	}

	const statClass& get(statEnum type) const {
		return statsMap.at(type);
	}
	 
	bool hasStat(statEnum type) const {
		return statsMap.find(type) != statsMap.end();
	}

	// Make the JSON serializer a friend so it can see statsMap
	friend void to_json(nlohmann::json& j, const statsContainer& sc);
};

//json erialize the container
inline void to_json(nlohmann::json& j, const statsContainer& sc) {
	j = nlohmann::json::object();
	for (const auto&[key, stat] : sc.statsMap) {
		// convert enum key to string for JSON object keys
		j[statEnumToString(key)] = stat;  // uses to_json(statClass) via ADL
		// If you want numeric keys instead: j[std::to_string(static_cast<int>(key))] = stat;
	}
}

inline void from_json(const nlohmann::json& j, statsContainer& sc) {
	for (auto it = j.begin(); it != j.end(); ++it) {
		statEnum type = stringToStatEnum(it.key());
		if (type != statEnum::MISSINGTYPE && type != statEnum::COUNT) {
			statClass s = it.value().get<statClass>(); // uses from_json(statClass)
			sc.add(type, s);
		}
	}
}
