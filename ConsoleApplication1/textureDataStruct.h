#pragma once 
#include <string> 
#include "json.hpp"

struct textureDataStruct { 
	std::string key;
	std::string animationName;
	int frameNumber = 0;
	int totalFrames = 0;

	int width = 0;
	int height = 0;
	int hitBoxWidth = 0;
	int hitBoxHeight = 0;
	 
	int xOffset = 0;
	int yOffset = 0;

	bool loop = true;
	std::string chainAnimation;
};
inline void to_json(nlohmann::ordered_json& j, const textureDataStruct& t) {
	j = nlohmann::ordered_json{
		{"key", t.key},
		{"animationName", t.animationName},
		{"frameNumber", t.frameNumber},
		{"totalFrames", t.totalFrames},
		{"width", t.width},
		{"height", t.height},
		{"hitBoxWidth", t.hitBoxWidth},
		{"hitBoxHeight", t.hitBoxHeight},
		{"xOffset", t.xOffset},
		{"yOffset", t.yOffset},
		{"loop", t.loop},
		{"chainAnimation", t.chainAnimation}
	};
}

inline void from_json(const nlohmann::ordered_json& j, textureDataStruct& t) {
	j.at("key").get_to(t.key);
	j.at("animationName").get_to(t.animationName);
	j.at("frameNumber").get_to(t.frameNumber);
	j.at("totalFrames").get_to(t.totalFrames);
	j.at("width").get_to(t.width);
	j.at("height").get_to(t.height);
	j.at("hitBoxWidth").get_to(t.hitBoxWidth);
	j.at("hitBoxHeight").get_to(t.hitBoxHeight);
	j.at("xOffset").get_to(t.xOffset);
	j.at("yOffset").get_to(t.yOffset);
	j.at("loop").get_to(t.loop);
	j.at("chainAnimation").get_to(t.chainAnimation);
}