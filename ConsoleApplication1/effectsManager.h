#pragma once
#include "lightningManager.h"
#include "fireManager.h"

class effectsManager {

public:
	effectsManager();
	~effectsManager();
	lightningManager& getLightningManager() { return lightningSystem; }
	fireManager& getFireManager() { return fireSystem; }

private:

	lightningManager lightningSystem;
	fireManager fireSystem;
};

