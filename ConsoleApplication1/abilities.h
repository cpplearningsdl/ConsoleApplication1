#pragma once
#include <vector>
#include <memory>
#include <string>
#include "ability.h"

class abilities {
public: 
	void addAbility(const ability& masterAbility);
	 
	void removeAbility(const std::string& name);
	 
	ability* getAbility(const std::string& name);
	 
	const std::vector<std::unique_ptr<ability>>& getAll() const;

private:
	std::vector<std::unique_ptr<ability>> abilities; // polymorphic storage
};
