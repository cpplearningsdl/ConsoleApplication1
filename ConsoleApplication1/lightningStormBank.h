#pragma once
#include <string>
#include <unordered_map> 
#include <filesystem>
#include "lightningStormDef.h"
 

class lightningStormBank {
public:
    lightningStormBank();
    ~lightningStormBank();
    bool loadFromDirectory(const std::filesystem::path& path);
    const lightningStormDef* get(const std::string& id) const;

private:
    std::unordered_map<std::string, lightningStormDef> defs;
};