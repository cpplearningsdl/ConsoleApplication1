#pragma once
#include <string>
#include "SDLLerp.h"
#include "fireManager.h"
#include "fireStormBank.h"
#include "fireStorm.h" 
#include "fireGenerator.h"
#include "randomUtilityFunctions.h"


fireManager::fireManager() { 
}

fireManager::~fireManager() {
	fireStorms.clear();
	
}

 
void fireManager::addFireStorm(std::string defaultStormId) {
    fireStorm storm;
    storm.def = defaultStorms.get(defaultStormId);
 
    int fireCount = randomInt(storm.def.config.spawnParams.minFires, storm.def.config.spawnParams.maxFires);

    storm.fires.reserve(fireCount);
    fireGenerator::generateStorm(storm, fireCount);
    fireStorms.push_back(storm);
}

void fireManager::addFireStorm(std::string defaultStormId, fireStormSpawnParams fsp, bool overrideSpawnParams) {
	fireStorm storm;
	storm.def = defaultStorms.get(defaultStormId);

	if (overrideSpawnParams) {
		storm.def.config.spawnParams = fsp;
	}
	int fireCount = randomInt(storm.def.config.spawnParams.minFires, storm.def.config.spawnParams.maxFires);

	storm.fires.reserve(fireCount); 
	fireGenerator::generateStorm(storm, fireCount);
	fireStorms.push_back(storm);
}

void fireManager::update(float dt) { 
    //CONSIDER ERASING FIRST THEN UPDATE SO YOU CAN BUILD BATCHES WHILE ITERATING?
	for (auto& storm : fireStorms) {
		storm.update(dt); 
	}

	fireStorms.erase(std::remove_if(fireStorms.begin(),	fireStorms.end(),[](const fireStorm& storm) {
        return storm.age > storm.def.config.stormDuration;
        }),
        fireStorms.end());

    buildLineBatch();
    buildEmberBatch();
}

void fireManager::buildEmberBatch() { 
    emberBatch.points.clear();
    emberBatch.colors.clear();

        for (const auto& storm : fireStorms) {
            for (const auto& fire : storm.fires) {
                for (const auto& ember : fire.embers) { 
                    emberBatch.points.push_back(ember.pos);
                    emberBatch.colors.push_back(ember.color);
                }
            }
        }

}
void fireManager::buildLineBatch() {
	lineBatch.starts.clear();
	lineBatch.ends.clear();
	lineBatch.colors.clear();

    for (const auto& storm : fireStorms) {
        const auto& profile = storm.def.config.colorProfile;

        for (const auto& f : storm.fires) {

            for (const auto& line : f.primary) {
                lineBatch.starts.push_back(line.start);
                lineBatch.ends.push_back(line.end);
                lineBatch.colors.push_back(
                    lerpColor(profile.primaryMin, profile.primaryMax, line.colorT)
                );
            }

            for (const auto& line : f.secondary) {
                lineBatch.starts.push_back(line.start);
                lineBatch.ends.push_back(line.end);
                lineBatch.colors.push_back(
                    lerpColor(profile.secondaryMin, profile.secondaryMax, line.colorT)
                );
            }
        }
    }
}
 

void fireManager::render(SDL_Renderer* renderer) const {

}