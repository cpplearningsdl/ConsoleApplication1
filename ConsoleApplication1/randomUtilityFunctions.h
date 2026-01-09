#pragma once
#include <random>
#include <cmath>

extern std::mt19937 gRng;

void initRng(uint32_t seed);



inline int randomInt(int min, int max) { 
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gRng);
}

inline float randomFloat(float min, float max) { 
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gRng);
}
