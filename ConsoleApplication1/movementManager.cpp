#pragma once
#include "movementManager.h"
#include "overLoaded.h"
#include "entity.h"

 

void movementManager::handleMovement(turnContext& ctx, entity* e) {
	if (e->moving()) {
		//finished to current waypoint
		if (e->getMovement().isFinished()) {
			movementPath& p = e->getPath();
			popWayPoint(p);
			//finished path
			if (pathFinished(p)) {
				e->setMoving(false); 
				ctx.events.emplace_back(finishedPathEvent(e, e->getId()));
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

 void movementManager::processEvent(turnContext& ctx, const gameEvent& ev) {
		 std::visit(overloaded{
		[&](const movementProposedEvent& e) {
			 // Approve or modify the move
			 if (true) {
				 true;
			 }
				else {
						// could push interrupt event here
					}
				},
			[&](const enteredTileEvent&) {}, // irrelevant
			[&](const entityDiedEvent&) {}, // irrelevant
			[](auto&) {}
				}, ev);

 }

 void movementManager::executeEvent(turnContext& ctx, const gameEvent& ev) {
	 std::visit(overloaded{
	[&](const movementProposedEvent& e) {
		 // Approve or modify the move
		 if (e.accepted) { 
			 e.mover->setMoving(true);
			 e.mover->getPath()= movementPath(e.newPath); 
			 e.mover->getMovement().init(e.mover->getMovement().getPos(), getNextWaypoint(e.mover->getPath()), 0.2f);
		 }
			else {
			 // could push interrupt event here
		 }
	 },
 [&](const finishedPathEvent&) {},
 [&](const enteredTileEvent&) {}, // irrelevant
 [&](const entityDiedEvent&) {}, // irrelevant
 [](auto&) {}
		 }, ev);

 }