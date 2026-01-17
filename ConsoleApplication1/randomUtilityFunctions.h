#pragma once
#include <random>
#include <cmath>
#include <SDL3/SDL.h>


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
inline bool randomBool(float probability = 0.5f){
    std::bernoulli_distribution dist(probability);
    return dist(gRng);
}

inline SDL_FPoint randomOffsetInRadius(float radius) {
    float angle = randomFloat(0.0f, 6.283185f);
    float r = std::sqrt(randomFloat(0.0f, 1.0f)) * radius;

    return {
        std::cos(angle) * r,
        std::sin(angle) * r
    };
}