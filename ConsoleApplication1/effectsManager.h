#pragma once
#include "lightningManager.h"
#include "fireManager.h"
#include "particleManager.h"
#include "rainManager.h"

class effectsManager {

public:
	effectsManager();
	~effectsManager();
	lightningManager& getLightningManager() { return lightningSystem; }
	fireManager& getFireManager() { return fireSystem; }
	particleManager& getParticleManager() { return particleSystem; }
	rainStormManager& getRainManager() { return rainSystem; }

private:

	lightningManager lightningSystem;
	fireManager fireSystem;
	particleManager particleSystem;
	rainStormManager rainSystem;
};

