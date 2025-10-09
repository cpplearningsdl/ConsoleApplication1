#pragma once
#include <string>
#include <vector>
#include "dimensions.h"
#include "position.h"
#include "entityOverrides.h"
#include "json.hpp"
using json = nlohmann::ordered_json;

struct levelData {
	struct stateStruct {
		int nextEntityId;//pass from level to level
		int number{};
		std::string name;

		dimensions mapSize;
		position viewPort;

		std::vector<int> tileIds;
		std::vector<int> entityIds;
		std::vector<int> specialIds;
		std::vector<int> objectives;
		std::vector<entityOverride> entityOverrides;
	}; 
	stateStruct state;
};

 
inline void to_json(json& j, const levelData::stateStruct& s) {
	j = json{
		{"nextEntityId", s.nextEntityId},
		{"number", s.number},
		{"name", s.name},
		{"tileIds", s.tileIds},
		{"factoryIds", s.entityIds},
		{"specialIds", s.specialIds},
		{"objectives", s.objectives},
		{"entityOverrides", s.entityOverrides}
	};
}

inline void from_json(const json& j, levelData::stateStruct& s) {
	j.at("nextEntityId").get_to(s.nextEntityId);
	j.at("number").get_to(s.number);
	j.at("name").get_to(s.name);
	j.at("tileIds").get_to(s.tileIds);
	j.at("factoryIds").get_to(s.entityIds);
	j.at("specialIds").get_to(s.specialIds);
	j.at("objectives").get_to(s.objectives);
	j.at("entityOverrides").get_to(s.entityOverrides);
} 
// whole levelData
inline void to_json(json& j, const levelData& l) {
	j = json{
		{"defaultState", l.state}
	};
}

inline void from_json(const json& j, levelData& l) {
	j.at("defaultState").get_to(l.state);
}

