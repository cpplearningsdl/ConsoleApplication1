#pragma once
#include <string>
#include <unordered_map>
#include "particleStormDef.h"

class particleStormBank {
public: 
	~particleStormBank();
	particleStormBank();

	bool loadFromDirectory(const std::filesystem::path& path);
	const particleStormDef get(const std::string& id) const; 

private:
    std::unordered_map<std::string, particleStormDef> defs;
};


 