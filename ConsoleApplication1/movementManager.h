#pragma once
#include "logManager.h"
#include "turnContext.h"

class entity;

class movementManager {

private:

public:
	void handleMovement(turnContext& ctx, entity* e);
	void processEvent(turnContext& ctx, const gameEvent& ev);
	void executeEvent(turnContext& ctx, const gameEvent& ev);
};