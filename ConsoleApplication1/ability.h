#pragma once
#include <string>
#include <memory>

class gameContext; // forward declaration

class ability {
public:
	ability(const std::string& name, int maxUses, int baseDamage);
	virtual ~ability() = default;

	// Polymorphic interface
	virtual std::unique_ptr<ability> clone() const = 0;   // force subclasses to implement
	virtual void executeEffect(gameContext& ctx) = 0;     // force subclasses to implement

	// Getters
	const std::string& getName() const;
	int getMaxUses() const;
	int getRemainingUses() const;

	// Runtime logic
	void addUses(int amount); 
	bool isExhausted() const;

protected:
	std::string name;
	int maxUses;
	int baseDamage;

	// Mutable state for this entity's copy
	int remainingUses;
};

