#pragma once
#include "lightningManager.h"

class effectsManager {

public:
	effectsManager();
	~effectsManager();
	lightningManager& getLightningManager() { return lightningSystem; }


private:

	lightningManager lightningSystem;
};

