#include "game.h"
#include <iostream>
#include <memory> 
#include "levelLoader.h"
#include "eventSystem.h"
#include "event.h"
#include "movementEvents.h"
#include "dialogueEvents.h"
#include "entityIncludes.h"
#include "entityTypeEnum.h"
#include "movementManager.h" 
#include "dialogueManager.h"
#include "renderCacheManager.h"

 
game::game() {
	loadALevel(1);
	dialogueManager.setStringDatabase(1);
	dialogueManager.setDialogueNodesDatabase(1);
	//dialogueManager.startDialogue(1);
	turnManager.getTurnCtx().emitEvent<dialogueProposalEvent>(1); 
	//startRotation(view, { 64, 64 }, 1,128.0f, 0.033f, false, 0.3f);
	//auto& ents = entityHandler.getEntities();
	//ents.back()->setMoving(true);
	//turnManager.getTurnCtx().events.emplace_back(
	//	std::make_unique<movementProposedEvent>(
	//		ents.back().get(),
	//		ents.back()->getId(),
	//		movementPath({ {1300,900},{150,50}, {20,120}, {0,0} }, { 0,0 }, { 1300,900 }),
	//		true
	//	)
	//); 
}

game::~game() {
	// cleanup
}
 
void game::update(inputManager& input) {
	updateCount++;
	gamePhase phase = turnManager.getTurnCtx().phase;
	switch (phase)
	{
		case gamePhase::NEWGAME: ;
			break;
		case gamePhase::DECISION: 

			updateEntities(entityHandler.getEntities());
			break;
		case gamePhase::ANIMATION:
			break;
		case gamePhase::MOVEMENT:

		case gamePhase::DIALOGUE:
			break;
	}
	updateView();//THIS MIGHT NEED TO BE CALLED FIRST
}
 
void game::updateEntities(std::vector<std::unique_ptr<entity>>& entitiesVector) {
	for (auto& e : entitiesVector) {
		e->getAnimationManager().step();
		//pass view to handleEvents??
		movementManager.handleMovement(turnManager.getTurnCtx(), e.get());
		handleEvents(turnManager.getTurnCtx(), entityHandler, movementManager, renderCacheHandler, dialogueManager);
	}
}

void game::loadALevel(int l) {
	loadLevel(*this, l);
}

 
void game::updateView() { 
	if (view.moving) { 
		moveView(view); 
		renderCacheHandler.generateEntityRenderablesCache(this->view, entityHandler.getEntities());
		renderCacheHandler.generateTileRenderablesCache(this->view, entityHandler.getFloorMap());
	}
	if (view.rotating) {
		updateRotation(this->view);
	}
	turnManager.getTurnCtx().cameraViewPos = view.viewPos;
}

 
 