#include "game.h"
#include <iostream>
#include <memory> 
#include "levelLoader.h"
#include "entityIncludes.h"
#include "entityTypeEnum.h"
#include "movementManager.h" 
#include "renderCacheManager.h"

 
game::game() {
	loadALevel(1);
	startRotation(view, { 64, 64 }, 1,128.0f, 0.033f, false, 0.3f);
}

game::~game() {
	// cleanup
}

//void game::update(inputManager& input) {
//	updateCount++;
//	updateEntities(entityHandler.getEntities());
//	updateEntities(entityHandler.getTiles());
//	updateView();
//}
void game::update(inputManager& input) {
	updateCount++;
	switch (turnCtx.phase)
	{
		case gamePhase::STARTTURN: newTurn();
			break;

	}
	updateView();
}
void game::newTurn() {
	clearCtx(turnCtx);

}
void game::updateEntities(std::vector<std::unique_ptr<entity>>& entitiesVector) {
	for (auto& e : entitiesVector) {
		e->getAnimationManager().step();
		movementManager.handleMovement(turnCtx, e.get()); 
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
}

 
 