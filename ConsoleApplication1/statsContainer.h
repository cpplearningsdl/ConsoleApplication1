#pragma once
//#include <unordered_map>
#include <map>
#include "statClass.h"
#include "statEnum.h"
#include "logManager.h"
#include "json.hpp"

class statsContainer {
private:
	std::map<statEnum, statClass> statsMap;

public:
	statsContainer() = default;
	statsContainer(const statsContainer&) = default;
	statsContainer& operator=(const statsContainer&) = default;

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
	friend void to_json(nlohmann::ordered_json& j, const statsContainer& sc);
	friend void from_json(const nlohmann::ordered_json& j, statsContainer& sc);
};

//json erialize the container
inline void to_json(nlohmann::ordered_json& j, const statsContainer& sc) {
	j = nlohmann::ordered_json::object();
	for (const auto&[key, stat] : sc.statsMap) {
		// convert enum key to string for JSON object keys
		j[statEnumToString(key)] = stat;  // uses to_json(statClass) via ADL
		// If you want numeric keys instead: j[std::to_string(static_cast<int>(key))] = stat;
	}
} 

inline void from_json(const nlohmann::ordered_json& j, statsContainer& sc) {
	for (auto it = j.begin(); it != j.end(); ++it) {
		statEnum type = stringToStatEnum(it.key());
		if (type != statEnum::STATENUMMISSINGTYPE && type != statEnum::STATENUMCOUNT) {
			statClass s;
			from_json(it.value(), s);  // <- use this instead of get<statClass>()
			sc.add(type, std::move(s));
		}
	}
}

