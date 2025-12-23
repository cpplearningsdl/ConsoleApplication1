#pragma once

enum class lightningMovementEnum {
    NONE, 
    MOVEENDPOINTS,        // start/end move, geometry rebuilt
    TRANSLATESTRIKE,      // entire strike translated, no rebuild
    MOVETOWARDPOINT       // moves toward a target point
};