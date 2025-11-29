#pragma once

#include "movementEvents.h"
#include "movementManager.h" 

 
void movementProposedEvent::process(turnContext& ctx, movementManager& move) {
    // forward to movementManager's strongly-typed handler
    move.processMovementProposed(ctx, *this);
}

void movementProposedEvent::execute(turnContext& ctx, movementManager& move) {
    move.executeMovementProposed(ctx, *this);
}

void finishedMovementEvent::process(turnContext& ctx, movementManager& move) {
    // forward to movementManager's strongly-typed handler
    move.processFinishedMovement(ctx, *this);
}

void finishedMovementEvent::execute(turnContext& ctx, movementManager& move) {
    move.executFinishedMovement(ctx, *this);
}

void finishedPathEvent::process(turnContext& ctx, movementManager& move) {
    // forward to movementManager's strongly-typed handler
    move.processFinishedPath(ctx, *this);
}

void finishedPathEvent::execute(turnContext& ctx, movementManager& move) {
    move.executeFinishedPath(ctx, *this);
}
