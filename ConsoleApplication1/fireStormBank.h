#pragma once
#include <string>
#include <unordered_map> 
#include <filesystem>
#include "fireStormDef.h"



class fireStormBank {
public:
	~fireStormBank();
	fireStormBank();

	bool loadFromDirectory(const std::filesystem::path& path);
	const fireStormDef get(const std::string& id) const;
private:
	std::unordered_map<std::string, fireStormDef> defs;
};