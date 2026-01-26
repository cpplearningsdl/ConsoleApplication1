#pragma once
#include "lightningManager.h"
#include "fireManager.h"
#include "particleManager.h"

class effectsManager {

public:
	effectsManager();
	~effectsManager();
	lightningManager& getLightningManager() { return lightningSystem; }
	fireManager& getFireManager() { return fireSystem; }
	particleManager& getParticleManager() { return particleSystem; }

private:

	lightningManager lightningSystem;
	fireManager fireSystem;
	particleManager particleSystem;
};

