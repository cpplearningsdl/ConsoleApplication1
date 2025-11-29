#pragma once
#include "movementManager.h" 
#include "entity.h"
#include "event.h"
#include "movementEvents.h"
 

void movementManager::handleMovement(turnContext& ctx, entity* e) {
	if (e->moving()) {
		//finished to current waypoint
		if (e->getMovement().isFinished()) {
			movementPath& p = e->getPath();
			popWayPoint(p);
			//finished path
			if (pathFinished(p)) {
				e->setMoving(false);  
				ctx.events.emplace_back(std::make_unique<finishedPathEvent>(e, e->getId(), p.destination));
			}
			//continue path
			else { 
				e->getMovement().init(e->getMovement().getPos(), getNextWaypoint(e->getPath()), e->getMovement().getSpeed());
			}
		}
		//continue to waypoint
		else {
			e->getMovement().step();
		}
	}
 }

void movementManager::processMovementProposed(turnContext& ctx, movementProposedEvent& ev) {
 
}

void movementManager::executeMovementProposed(turnContext& ctx, movementProposedEvent& ev) {
	handleMovementProposedEvent(ev);
}


void movementManager::processFinishedMovement(turnContext& ctx, finishedMovementEvent& ev) {

}
void movementManager::executFinishedMovement(turnContext& ctx, finishedMovementEvent& ev) {

}

void movementManager::processFinishedPath(turnContext& ctx, finishedPathEvent& ev) {

}

void movementManager::executeFinishedPath(turnContext& ctx, finishedPathEvent& ev) {

}

 void movementManager::handleMovementProposedEvent(movementProposedEvent& ev) {
	 if (ev.accepted)
	 {
		 ev.mover->setMoving(true);
		 ev.mover->getPath() = movementPath(ev.newPath);
		 ev.mover->getMovement().init(ev.mover->getMovement().getPos(), getNextWaypoint(ev.mover->getPath()), 0.2f);
	  } 
 }