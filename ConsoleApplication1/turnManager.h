#pragma once
#include "turnContext.h"

class entity;

class turnManager
{
public: 
	turnManager();

	turnContext& getTurnCtx() { return turnCtx; }
	void newTurn();
	void handleEvent(  baseEvent* event);
private:
	turnContext turnCtx;
};

