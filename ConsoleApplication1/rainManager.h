#pragma once 
#include <vector>
#include <string>
#include "json.hpp"
#include "rainStorm.h" 
#include "rainStormBank.h"  
#include "fireLineBatch.h"

using json = nlohmann::ordered_json;

class rainStormManager {

public:

	rainStormManager();
	~rainStormManager();
	void update(float dt);
	void addRainStorm(const std::string& id);
	void addRainStorm(const std::string id,rainStormSpawnParams& p);
	void buildRainBatch();
	void reserveBatchesForAllStorms();
	fireLineBatch& getPrimaryBatch() { return primaryColorDropBatch; };
	fireLineBatch& getSecondaryBatch() { return secondaryColorDropBatch; };

private:
	std::vector<rainStorm> storms;
	rainStormBank stormBank;
	fireLineBatch primaryColorDropBatch;//<<<<<<<<<<<
	fireLineBatch secondaryColorDropBatch;//<<<<<<<<<<<
};