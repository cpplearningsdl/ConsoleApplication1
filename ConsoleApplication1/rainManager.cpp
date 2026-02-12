#include "rainManager.h"
#include <vector>
#include <string>
#include "json.hpp"
#include "rainStorm.h"


rainStormManager::rainStormManager() {

}
rainStormManager::~rainStormManager() {
	storms.clear(); 
}


void rainStormManager::update(float dt) {
    for (auto& storm : storms) {
        storm.update(dt);
    }
    for (size_t i = 0; i < storms.size(); ) {
        if (storms[i].age > storms[i].def.config.stormDuration) {
            storms[i] = storms.back();
            storms.pop_back(); 
            dropBatch.clear();
        }
        else { ++i; }
    }
    if (!storms.empty()) {
        buildRainBatch();
    }
};


void rainStormManager::addRainStorm(const std::string& id) {
    storms.emplace_back();
    auto& s = storms.back();

    s.def = stormBank.get(id);

    const float expected = s.def.config.spawnParams.dropsPerSecond * s.def.config.stormDuration;

    s.drops.reserve(static_cast<size_t>(std::ceil(expected * 1.10f)));
    s.updateActualParams();
};

void rainStormManager::addRainStorm(const std::string id, rainStormSpawnParams& p) {
    storms.emplace_back();
    auto& s = storms.back();

    s.def = stormBank.get(id);

    const float expected = s.def.config.spawnParams.dropsPerSecond * s.def.config.stormDuration;

    s.drops.reserve(static_cast<size_t>(std::ceil(expected * 1.10f)));
    s.updateActualParams();
};

void rainStormManager::buildRainBatch() {
};