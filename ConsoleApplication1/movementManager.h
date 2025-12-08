#pragma once
#include "logManager.h" 
#include "event.h" 

class entity;
struct movedThisFrameEvent;
struct movementProposedEvent;
struct finishedMovementEvent;
struct finishedPathEvent;
struct turnContext;

class movementManager {

private:

public:
	void handleMovement(turnContext& ctx, entity* e);
	void handleMovementProposedEvent(movementProposedEvent& e);

	void processMovementProposedEvent(turnContext& ctx, movementProposedEvent& ev, eventPhase p);
	void processMovedThisFrameEvent(turnContext& ctx,movedThisFrameEvent& ev, eventPhase p);
	void processFinishedMovementEvent(turnContext& ctx, finishedMovementEvent& ev, eventPhase p);
	void processFinishedPathEvent(turnContext& ctx, finishedPathEvent& ev, eventPhase p);
};