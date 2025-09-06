#pragma once
#include <string>
#include <memory>
#include "abilityType.h" 

class gameContext;

class ability {
public:
	 
	ability();
	virtual ~ability() = default;

	// Polymorphic interface
	virtual std::unique_ptr<ability> clone() const = 0;
	virtual void executeEffect(gameContext& ctx) = 0;   

	void setName(const std::string& newName) { name = newName; }
	const std::string& getName() const;
	abilityType getAbilityType() const; 
	void setAbilityType(abilityType newType);
	  
protected:
	std::string name;
	abilityType type; 
};

