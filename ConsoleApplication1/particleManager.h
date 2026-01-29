#pragma once
#include <vector>
#include "json.hpp"
#include "particleStorm.h" 
#include "particleBank.h" 
#include "particleBatch.h"

using json = nlohmann::ordered_json;

class particleManager {

public:

	particleManager();
	~particleManager();
	void update(float dt);
	void addParticleStorm(const std::string& id);
	void addParticleStorm(const std::string id, particleSpawnParams& p);
	void buildParticleBatch();
	particleBatch& getParticleBatch() { return particleBatch; };

private:
	std::vector<particleStorm> storms;
	particleStormBank defaults;
	particleBatch particleBatch;
};