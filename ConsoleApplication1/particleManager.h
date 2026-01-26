#pragma once
#include <vector>
#include "json.hpp"
#include "particleStorm.h" 
#include "particleBank.h" 

using json = nlohmann::ordered_json;

class particleManager {

public:

	particleManager();
	~particleManager();
	void update(float dt);
	void addParticleStorm(const std::string& id);
	void addParticleStorm(const std::string id, particleSpawnParams& p);


	void update(float dt);
private:
	std::vector<particleStorm> storms;
	particleStormBank defaults;

};