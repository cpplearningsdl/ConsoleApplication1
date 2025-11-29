#pragma once
#include "logManager.h"
#include "turnContext.h"
#include "event.h"

class entity;
struct movementProposedEvent;
struct finishedMovementEvent;
struct finishedPathEvent;

class movementManager {

private:

public:
	void handleMovement(turnContext& ctx, entity* e);
	void handleMovementProposedEvent(movementProposedEvent& e);

	void processMovementProposed(turnContext& ctx, movementProposedEvent& ev);
	void executeMovementProposed(turnContext& ctx, movementProposedEvent& ev);

	void processFinishedMovement(turnContext& ctx, finishedMovementEvent& ev);
	void executFinishedMovement(turnContext& ctx, finishedMovementEvent& ev);

	void processFinishedPath(turnContext& ctx, finishedPathEvent& ev);
	void executeFinishedPath(turnContext& ctx, finishedPathEvent& ev);


};