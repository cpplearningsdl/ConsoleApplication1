#pragma once
#include "randomUtilityFunctions.h"
#include "logManager.h"
#include <random>
#include <cmath>
#include <string>


std::mt19937 gRng;

void initRng(uint32_t seed) {
    gRng.seed(seed); 
    logManager::logThis("Seeded gRng with seed: ", std::to_string(seed));
}