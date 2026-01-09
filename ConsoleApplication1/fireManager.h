#pragma once
#include <vector>
#include <string>
#include <random>

#include "logManager.h"
#include "fireStorm.h"

class fireManager {
public: 
	fireManager();
	~fireManager();

	void addFireStorm();
	void update(float dt);
	void render(SDL_Renderer* renderer) const;

private:
	std::vector<fireStorm> fireStorms; 
	std::mt19937 rng{ std::random_device{}() };
};