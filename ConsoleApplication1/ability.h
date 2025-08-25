#pragma once
#include <string>
#include <memory>
#include "abilityType.h"
#include "uses.h"

class gameContext;

class ability {
public:
	 
	ability(const std::string& name, int maxUses, int basePower, int currentPower);
	virtual ~ability() = default;

	// Polymorphic interface
	virtual std::unique_ptr<ability> clone() const = 0;
	virtual void executeEffect(gameContext& ctx) = 0;   

 
	const std::string& getName() const;
	abilityType getAbilityType() const; 
	int getBasePower() const;
	int getCurrentPower() const;
	 
	void setCurrentPower(int amount);
	 
	void increaseCurrentPower(int amount);

	void reset();
	  
protected:
	std::string name;
	abilityType abilityType;
	int basePower;
	int currentPower;
	uses uses;
};

