#pragma once
#include "logManager.h"
#include "turnContext.h"
#include "event.h"

class entity;

class movementManager {

private:

public:
	void handleMovement(turnContext& ctx, entity* e);
	void handleMovementProposedEvent(baseEvent* ev);
	void processEvent(turnContext& ctx, baseEvent* ev);
	void executeEvent(turnContext& ctx, baseEvent* ev);
};