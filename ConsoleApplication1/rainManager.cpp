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
            if (storms[i].def.config.sequence.continueSequence) { 
                addRainStorm(storms[i].def.config.sequence.nextStormId, storms[i].overrideParams);
            }
            storms[i].drops.clear();
            storms[i] = storms.back();
            storms.pop_back(); 
        }
        else { ++i; } 
    }
    //clear here or drops stay on screen after storm ends because this never gets called if storms is empty in the next block, and it will  be empty when the previous block pops the last storm
    primaryColorDropBatch.clear();
    secondaryColorDropBatch.clear();

    if (!storms.empty()) { 
        reserveBatchesForAllStorms();
        buildRainBatch();
    }
};


void rainStormManager::addRainStorm(const std::string& id) {
    storms.emplace_back();
    auto& s = storms.back(); 
    s.def = stormBank.get(id);
    s.updateActualParams();
    s.actualKillParams = s.def.config.killParams;
    s.wind.currentAngleDeg = s.def.config.windParams.startAngleDeg;

    s.emitCutOff = s.def.config.stormDuration * s.def.config.spawnParams.emitTime;
    const float expected = s.def.config.emitParams.dropsPerSecond * s.def.config.stormDuration;   
    s.drops.reserve(static_cast<size_t>(std::ceil(expected * 1.10f))); 

};
 
void rainStormManager::addRainStorm(const std::string id, rainOverrideParams rop) {
    storms.emplace_back();
    auto& s = storms.back();  
    
    s.overrideParams.overrideSpawn = rop.overrideSpawn;
    s.overrideParams.spawnOverrides = rop.spawnOverrides;
    s.def = stormBank.get(id); 
    
    s.updateActualParams();
    s.actualKillParams = s.def.config.killParams;

    s.wind.currentAngleDeg = s.def.config.windParams.startAngleDeg;

    s.emitCutOff = s.def.config.stormDuration * s.def.config.spawnParams.emitTime;
    const float expected = s.def.config.emitParams.dropsPerSecond * s.def.config.stormDuration; 
    s.drops.reserve(static_cast<size_t>(std::ceil(expected * 1.10f))); 
};

void rainStormManager::reserveBatchesForAllStorms() {
    size_t expectedPrimary = 0;
    size_t expectedSecondary = 0;

    for (const auto& s : storms)
    {
        float expectedDrops = s.def.config.emitParams.dropsPerSecond * s.age;

        expectedDrops *= 1.10f; // safety margin

        float secChance = s.def.config.colors.secondaryChance;

        expectedSecondary += static_cast<size_t>(std::ceil(expectedDrops * secChance));
        expectedPrimary += static_cast<size_t>(std::ceil(expectedDrops * (1.0f - secChance)));
    }
     
    primaryColorDropBatch.reserve(expectedPrimary);
    secondaryColorDropBatch.reserve(expectedSecondary);
}


void rainStormManager::buildRainBatch() {
    primaryColorDropBatch.clear();
    secondaryColorDropBatch.clear();
    for (const auto& s : storms) {
        for (const auto& d : s.drops)
        {
            if (!d.isPrimary())
            {
                secondaryColorDropBatch.starts.push_back(d.start);
                secondaryColorDropBatch.ends.push_back(d.end);
                secondaryColorDropBatch.colors.push_back(d.color);
            }
            else
            {
                primaryColorDropBatch.starts.push_back(d.start);
                primaryColorDropBatch.ends.push_back(d.end);
                primaryColorDropBatch.colors.push_back(d.color);
            }
        }
    }
};