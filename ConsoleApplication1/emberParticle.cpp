#include "emberParticle.h"
#include <random>


void emberParticle::update(float dt) {
    switch (movement) {
    case emberMovementEnum::RISE:
        velocity.y -= 10.0f * dt;
        break;
    case emberMovementEnum::RISEANDFAN:
        velocity.x += ((float(rand()) / RAND_MAX) - 0.5f) * 30.0f * dt;
        velocity.y -= 15.0f * dt;
        break;
    case emberMovementEnum::ARC:
        velocity.y += 40.0f * dt;
        break;
    case emberMovementEnum::DRIFT:
        velocity.x += ((float(rand()) / RAND_MAX) - 0.5f) * 4.0f * dt;
        velocity.y += ((float(rand()) / RAND_MAX) - 0.5f) * 4.0f * dt;
        break;
    }

    pos.x += velocity.x * dt;
    pos.y += velocity.y * dt;
    age += dt;

}