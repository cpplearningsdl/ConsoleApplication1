#pragma once
#include <vector>
#include <string>
#include "ability.h"

class Abilities {
public:
	// Add a new ability by copying a master ability
	void addAbility(const ability& masterAbility);

	// Remove ability by name
	void removeAbility(const std::string& name);

	// Get ability by name
	ability* getAbility(const std::string& name);

	// Access all abilities (read-only)
	const std::vector<ability>& getAll() const;

private:
	std::vector<ability> abilities; // entity owns unique copies
};