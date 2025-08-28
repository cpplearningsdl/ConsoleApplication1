#pragma once
#include <unordered_map>
#include "statClass.h"
#include "statEnum.h"
#include "logManager.h"

class stats {
private:
	std::unordered_map<statEnum, statClass> statsMap;

public:
	stats() = default;
	 
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
};
