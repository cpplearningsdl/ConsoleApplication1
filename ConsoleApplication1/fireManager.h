#pragma once
#include <vector>
#include <string>
#include <random> 
#include "logManager.h"
#include "fireGenerator.h"
#include "fireStorm.h"
#include "fireStormBank.h"
#include "fireLineBatch.h"
#include "particleBatch.h"

class fireManager {
public: 
	fireManager();
	~fireManager();

	void addFireStorm(std::string id);
	void addFireStorm(std::string id, fireStormSpawnParams fsp, bool overrideSpawnParams);
	void update(float dt);
	void buildLineBatch(); 
	void buildEmberBatch();
	void render(SDL_Renderer* renderer) const;
	std::vector<SDL_FPoint>& getStarts() { return lineBatch.starts; }
	std::vector<SDL_FPoint>& getEnds() { return lineBatch.ends; }
	particleBatch& getEmbers() { return emberBatch; }
	fireLineBatch& getFireLineBatch() { return lineBatch; }

private:
	fireGenerator fireGenerator;

	std::vector<fireStorm> fireStorms; 
	fireStormBank defaultStorms;

	fireLineBatch lineBatch;
	particleBatch emberBatch;
	 
};