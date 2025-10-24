#pragma once
#include "movementManager.h"
#include "overLoaded.h"

 void movementManager::handleMovement(turnContext& ctx, entity* e) {
	//animationManager& eam = e.getAnimationManager();

	//if (e.moving()) {
	//	if (eam.isFinished()) {//this is checking if the animation is finished not if the movement is finished, but i believe the movement length is set to how many frames the animation is... test
	//		movementPath& p = e.getPath();
	//		if (p.turns.size() > 0) {
	//			//get waypoint dest and pass here..

	//			eam.setMovement(getNextDirection(p), 0, 0, 128, 10, 0, 0);//update for vecTo..
	//			logManager::logThis("HM");
	//		}
	//		else {//finished path
	//			e.setMoving(false);
	//			e.setBlockMenus(false);
	//			e.setUnblockMenu(true);
	//			eam.loadAnimation("idle");
	//			eam.setMovement(movementTypeEnum::idle, 0, 0, 0, eam.getFrameCount(), 0, 0);
	//		}
	//	}
	//}
}

 void movementManager::handleEvent(turnContext& ctx, const gameEvent& event) {
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
				}, event);

 }