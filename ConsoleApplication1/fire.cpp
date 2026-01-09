#include "fire.h"

void fire::update(float dt) {
    for (auto& l : primary)
        l.update(dt, size); 

    for (auto& l : secondary)
        l.update(dt, size);

    for (auto& e : embers)
        e.update(dt);

    embers.erase(
        std::remove_if(embers.begin(), embers.end(),
            [](const emberParticle& e) {
                return e.age >= e.lifetime;
            }),
        embers.end()
    );
}
