#pragma once
#include <string>
#include "position.h"
#include "json.hpp"

struct entityRenderInfo {
	std::string textureKey;
	position pos;
	bool render;  
};

// to_json
inline void to_json(nlohmann::ordered_json& j, const entityRenderInfo& s) {
	j = nlohmann::ordered_json{
		{ "textureKey", s.textureKey },
		{ "pos", s.pos }, 
		{ "render", s.render }
	};
}

// from_json
inline void from_json(const nlohmann::ordered_json& j, entityRenderInfo& s) {
	if (j.contains("textureKey")) {
		s.textureKey = j.at("textureKey").get<std::string>();
	}
	if (j.contains("pos")) {
		j.at("pos").get_to(s.pos);  
	}
	if (j.contains("render")) {
		s.render = j.at("render").get<bool>();
	}
}