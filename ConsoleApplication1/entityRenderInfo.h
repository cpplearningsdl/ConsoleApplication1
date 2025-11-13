#pragma once
#include <string>
#include "position.h"
#include "json.hpp"
#include <SDL3/SDL.h>

struct entityRenderInfo { 
	SDL_Texture* tex;
	position pos;
	float height;
	float width;
	bool render;  
};

inline void updateEntityRenderInfo(entityRenderInfo& eri, SDL_Texture* t, const position& pos, float h, float w, bool visible) {
	eri.tex = t;
	eri.pos = pos;
	eri.height = h;
	eri.width = w;
	eri.render = visible;

}
	
inline void to_json(nlohmann::ordered_json& j, const entityRenderInfo& s) {
	j = nlohmann::ordered_json{ 
		{ "pos", s.pos }, 
		{"height", s.height},
		{"width", s.width},
		{ "render", s.render }
	};
}

// from_json
inline void from_json(const nlohmann::ordered_json& j, entityRenderInfo& s) {  
	if (j.contains("pos")) {
		j.at("pos").get_to(s.pos);  
	}
	if (j.contains("height")) {
		s.height = j.at("height").get<float>();
	}
	if (j.contains("width")) {
		s.width = j.at("width").get<float>();
	}
	if (j.contains("render")) {
		s.render = j.at("render").get<bool>();
	}
}