#pragma once
#include "ability.h"
#include <iostream>

class healAbility : public ability {
public:
	healAbility() : ability("Heal", 10, 0, 0) {}

	std::unique_ptr<ability> clone() const override {
		return std::make_unique<healAbility>(*this);
	}

	void executeEffect(gameContext& ctx) override {
		std::cout << "Healed entity " << std::endl;
	}
};
