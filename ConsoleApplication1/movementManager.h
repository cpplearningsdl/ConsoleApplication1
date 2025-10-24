#pragma once
#include "logManager.h"
#include "turnContext.h"

class entity;

class movementManager {

private:

public:
	void handleMovement(turnContext& ctx, entity* e);
	void handleEvent(turnContext& ctx, const gameEvent& event);
};