#include "fireLine.h"
#include <algorithm>
#include <cmath>

void fireLine::update(float dt, const fireLineParams& cfg)
{
    // grow to full size
    if (currentLength < targetLength) {
        currentLength += cfg.growSpeed * dt;
        if (currentLength > targetLength)
            currentLength = targetLength;
    }

    // advance oscillators
    swayPhase += cfg.swaySpeed * dt;
    lengthPhase += cfg.lengthOscSpeed * dt;

    float lengthOsc =
        std::sin(lengthPhase) *
        (targetLength * cfg.lengthOscPct);

    float sway =
        std::sin(swayPhase) *
        cfg.swayAmplitude;

    float effectiveLength = currentLength + lengthOsc;

    // perpendicular direction for sway
    SDL_FPoint perp{ -dir.y, dir.x };

    end.x = start.x
        + dir.x * effectiveLength
        + perp.x * sway;

    end.y = start.y
        + dir.y * effectiveLength
        + perp.y * sway;

    //// color oscillation
    //colorT += colorDir * cfg.colorSpeed * dt;
    //if (colorT >= 1.0f) { colorT = 1.0f; colorDir = -1.0f; }
    //if (colorT <= 0.0f) { colorT = 0.0f; colorDir = 1.0f; }
}