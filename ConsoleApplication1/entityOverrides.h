#pragma once
#include "position.h"
#include "json.hpp"
using json = nlohmann::ordered_json;

struct entityOverride {
	int id;
	position pos;
};

// serialization
inline void to_json(json& j, const entityOverride& e) {
	j = json{
		{"id", e.id},
		{"pos", e.pos}  // uses existing position to_json/from_json
	};
}

inline void from_json(const json& j, entityOverride& e) {
	j.at("id").get_to(e.id);
	j.at("pos").get_to(e.pos);  // uses existing position serialization
}
