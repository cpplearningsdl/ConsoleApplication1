#pragma once
#include "movementManager.h" 
#include "entity.h"
#include "turnContext.h"
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
		ctx.emitEvent<movedThisFrameEvent>( e, e->getId(), e->getMovement().getPos());
	}
 }


void movementManager::processMovementProposedEvent(turnContext& ctx, movementProposedEvent& ev, eventPhase p) {
	handleMovementProposedEvent(ev);
}
void movementManager::processFinishedMovementEvent(turnContext& ctx, finishedMovementEvent& ev, eventPhase p) {
 
}
void movementManager::processFinishedPathEvent(turnContext& ctx, finishedPathEvent& ev, eventPhase p) {
 
}

  
 void movementManager::handleMovementProposedEvent(movementProposedEvent& ev) {
	 if (ev.accepted)
	 {
		 ev.mover->setMoving(true);
		 ev.mover->getPath() = movementPath(ev.newPath);
		 ev.mover->getMovement().init(ev.mover->getMovement().getPos(), getNextWaypoint(ev.mover->getPath()), 0.2f);
	  } 
 }