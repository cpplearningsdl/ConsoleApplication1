#pragma once
#include <string>
#include <memory>
#include "json.hpp"
#include "abilityType.h" 

class gameContext;

class ability {
public:
	 
	ability();
	virtual ~ability() = default;


	virtual std::unique_ptr<ability> clone() const = 0;
	virtual void executeEffect(gameContext& ctx) = 0;   

	void setName(const std::string& newName) { name = newName; }
	const std::string& getName() const;
	abilityType getAbilityType() const; 
	void setAbilityType(abilityType newType);
	virtual nlohmann::ordered_json to_Json() const = 0;
	virtual void from_Json(const nlohmann::ordered_json& j) = 0;

protected:
	std::string name;
	abilityType type; 
};

