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
		position viewPos;

		std::vector<int> turnOrder;
		std::vector<int> tileIds;
		std::vector<int> entityIds;
		std::vector<position>entityPositions;
		std::vector<int> specialIds;
		std::vector<int>specialIdPositions;
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
		{"mapSize", s.mapSize},
		{"viewPos"}, s.viewPos,
		{"tileIds", s.tileIds},
		{"entityIds", s.entityIds},
		{"entityPositions"}, s.entityPositions,
		{"specialIds", s.specialIds},
		{"SpecialIdPositions", s.specialIdPositions },
		{"objectives", s.objectives},
		{"entityOverrides", s.entityOverrides}
	};
}

inline void from_json(const json& j, levelData::stateStruct& s) {
	j.at("nextEntityId").get_to(s.nextEntityId);
	j.at("number").get_to(s.number);
	j.at("name").get_to(s.name);
	j.at("mapSize").get_to(s.mapSize);
	j.at("viewPos").get_to(s.viewPos);
	j.at("tileIds").get_to(s.tileIds);
	j.at("entityIds").get_to(s.entityIds);
	j.at("entityPositions").get_to(s.entityPositions);
	j.at("specialIds").get_to(s.specialIds);
	j.at("specialIdPositions").get_to(s.specialIdPositions);
	j.at("objectives").get_to(s.objectives);
	j.at("entityOverrides").get_to(s.entityOverrides);
} 
// whole levelData
inline void to_json(json& j, const levelData& l) {
	j = json{
		{"state", l.state}
	};
}

inline void from_json(const json& j, levelData& l) {
	j.at("state").get_to(l.state);
}

