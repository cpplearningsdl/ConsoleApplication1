#pragma once

#include <unordered_map>
#include <string>
#include "rainStormDef.h"


class rainStormBank {
public: 
    rainStormBank();
    ~rainStormBank();
    bool loadFromDirectory(const std::filesystem::path& path);
   const rainStormDef get(const std::string& id) const;

private:
    std::unordered_map<std::string, rainStormDef> defs;
};