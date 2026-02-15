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
//fordebug
#include "light.h"

 
game::game() {
	loadALevel(1);
	dialogueManager.setStringDatabase(1);
	dialogueManager.setDialogueNodesDatabase(1); 
	turnManager.getTurnCtx().emitEvent<dialogueProposalEvent>(1); 
	//startRotation(view, { 564, 564 }, 1,128.0f, 0.033f, false, 0.3f);
	//setViewTarget(view, { 500,500 }, .4);
	auto& ents = entityHandler.getEntities();
	ents.back()->setMoving(true);
	turnManager.getTurnCtx().events.emplace_back(
		std::make_unique<movementProposedEvent>(
			ents.back().get(),
			ents.back()->getId(),
			movementPath({ {1700,900},{150,50}, {20,120}, {0,0} }, { 0,0 }, { 1700,900 }),
			true
		)
	); 
	lightManager.addLight({ 64, 64 }, 110, 0.3f, { 177, 200, 150, 255 });
	auto& lite = lightManager.getLights().back();
	lite.setIntensityOscillation(0.6f, 0.4f);
	lite.setRadiusOscillation(0.9f, 0.4f); 
	//effectsManager.getLightningManager().addStorm("go-to", { 0, 0 }, { -1.0, -1.0 }, { 1950.0f, 1950.0f });
	effectsManager.getFireManager().addFireStorm("defaultFireStorm");
//	effectsManager.getParticleManager().addParticleStorm("defaultSpiralIn");
//	effectsManager.getParticleManager().addParticleStorm("bloodSpray");
	effectsManager.getParticleManager().addParticleStorm("ringInwardExplosion");

	//effectsManager.getRainManager().addRainStorm("defaultRadiusRainStorm");
	effectsManager.getRainManager().addRainStorm("defaultRadiusRainStorm");
//effectsManager.getLightningManager().addStorm("rotating_arc", { 950.0f, 350.0f }, { 950.0f, 350.0f });
//effectsManager.getLightningManager().addStorm("basic_storm", { 333.0f, 333.0f }, { 950.0f, 350.0f });
}

game::~game() {
	// cleanup
}
 
void game::update(inputManager& input, float deltaTime) {
	updateCount++;
	gamePhase phase = turnManager.getTurnCtx().phase;
	switch (phase)
	{
		case gamePhase::NEWGAME: ;
			break;
		case gamePhase::DECISION: 

			updateEntities(entityHandler.getEntities());
			dialogueManager.handleInput(input);
			dialogueManager.tickDialogue();
			lightManager.update(deltaTime);
			effectsManager.getLightningManager().update(deltaTime);//CONDENSE THIS INTO 1 EFFECT MANAGER CALL
			effectsManager.getFireManager().update(deltaTime);
			effectsManager.getParticleManager().update(deltaTime);
			effectsManager.getParticleManager().update(deltaTime);
			effectsManager.getRainManager().update(deltaTime);
			break;
		case gamePhase::ANIMATION:
			break;
		case gamePhase::MOVEMENT:

		case gamePhase::DIALOGUE:
			break;
	}
	updateView();//THIS MIGHT NEED TO BE CALLED FIRST
}

void game::updateDialogue(inputManager& input) {

}
void game::updateEntities(std::vector<std::unique_ptr<entity>>& entitiesVector) {
	for (auto& e : entitiesVector) {
		e->getAnimationManager().step(); 
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

 
 