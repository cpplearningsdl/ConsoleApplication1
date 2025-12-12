#pragma once
#include <vector> 
#include "entityIncludes.h"
#include "inputManager.h"
#include "entityManager.h"
#include "dialogueManager.h"
#include "renderCacheManager.h"
#include "movementManager.h"
#include "turnManager.h"
#include "level.h"
#include "view.h"

class game {
public:
	game();
	~game();

	void update(inputManager& input);
	void updateEntities(std::vector<std::unique_ptr<entity>>& entitiesVector);
 
	void loadALevel(int l);
	//void setLevelData(levelData&& d) noexcept { currentLevelData = std::move(d);}
	void setLevelData(levelData d) { currentLevelData = d; }
	levelData& getLevelData() noexcept { return currentLevelData; }
	const levelData& getLevelData() const noexcept { return currentLevelData; }
	
	void updateDialogue(inputManager& input);
	void updateView();
	const viewPort& getView() const { return view; }
	viewPort& getViewNonConst() { return view; }

	entityManager& getEntityHandler() { return entityHandler; }
	renderCacheManager& getRenderCacheManager() { return renderCacheHandler; }

	turnManager& getTurnManager() { return turnManager; }
	dialogueManager& getDialogueManager() { return dialogueManager; }
private: 
	int updateCount = 0;
	bool blockMenus = false;
	levelData currentLevelData;
	viewPort view;
	 
	entityManager entityHandler;
	renderCacheManager renderCacheHandler;
	movementManager movementManager;
	dialogueManager dialogueManager;
	turnManager turnManager;
	//std::vector<int> turnOrder;//Id's, have to keep track of their ID when saving then update to new runtime ID after loading save!!
}; 