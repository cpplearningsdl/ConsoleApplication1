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

 void movementManager::processEvent(turnContext& ctx, baseEvent* ev) {
 

 }

 void movementManager::executeEvent(turnContext& ctx, baseEvent* ev) {

	 switch (ev->type) {
	 case eventType::movementProposed: {
		 handleMovementProposedEvent(ev);
		 break;
	 } 
	 case eventType::finishedPath: {

		 break;
	 }
	 default:
		 break;
	 } 

 }

 void movementManager::handleMovementProposedEvent(baseEvent* ev) {

	 auto* e = dynamic_cast<movementProposedEvent*>(ev);
	 if (e->accepted) {
		 e->mover->setMoving(true);
		 e->mover->getPath() = movementPath(e->newPath);
		 e->mover->getMovement().init(e->mover->getMovement().getPos(), getNextWaypoint(e->mover->getPath()), 0.2f);
	 }  
 }