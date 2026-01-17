#include "fire.h"
#include "fireStormFireLineParams.h"
#include "fireGenerator.h"


void fire::update(float dt, fireStormFireLineParams& cfg, fireStormEmberParams& emberCfg) {

    if (emberCfg.embersPerFireMin > 0) {
        emberTimer += dt;

        if (emberTimer > emberCfg.emberInterval && embers.size() < emberCfg.embersPerFireMax) {
            emberTimer = 0.0f;
            embers.push_back(fireGenerator::generateEmber(emberCfg, origin));
        }
    }

    for (auto& l : primary)
        l.update(dt, cfg.primary);

    for (auto& l : secondary)
        l.update(dt, cfg.secondary);

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
