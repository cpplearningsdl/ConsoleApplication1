#include "fireLine.h"
#include <algorithm>
#include <cmath>

void fireLine::update(float dt, float size){
    end.x += velocity.x * dt;
    end.y += velocity.y * dt;

    velocity.x += ((float(rand()) / RAND_MAX) - 0.5f) * 12.0f * dt * size;
    velocity.y = std::clamp(velocity.y, -40.0f * size, -4.0f);

}