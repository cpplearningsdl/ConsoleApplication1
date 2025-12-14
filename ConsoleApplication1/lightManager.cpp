#pragma once
#include "lightManager.h"
#include "logManager.h"
#include "light.h"

lightManager::lightManager() {

}
lightManager::~lightManager() {
    lights.clear();
 
}


void lightManager::addLight(position p, float radius, float intensity, SDL_Color color) { 
    lights.push_back(light(p, radius, intensity, color));
}

void lightManager::update(float deltaTime) {
    for (auto& l : lights) {
        l.update(deltaTime);
    }
}