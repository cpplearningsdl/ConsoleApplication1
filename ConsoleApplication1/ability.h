#pragma once
#include <string>

class GameContext; // forward declaration if needed later

class ability {
public:
	ability(const std::string& name, int maxUses, int baseDamage);

	// Getters
	const std::string& getName() const;
	int getMaxUses() const;
	int getBaseDamage() const;
	int getRemainingUses() const;

	// Runtime logic
	void decrementUses();
	bool isExhausted() const;

	// Example effect logic (may use game context later)
	// For now we just define interface; actual effect executed elsewhere
	void executeEffect(GameContext& ctx);

private:
	std::string name;
	int maxUses;
	int baseDamage;

	// Mutable state for this entity's copy
	int remainingUses;
};

