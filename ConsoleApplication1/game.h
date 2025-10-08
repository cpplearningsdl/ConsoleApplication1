#pragma once
#include <vector> 
#include "entityIncludes.h"
#include "inputManager.h"
#include "view.h"

class game {
public:
	game();
	~game();

	void update(inputManager& input);
	entity&  getEntityById(int id);
	std::vector<std::unique_ptr<entity>>& getEntities() { return entities; } 
	const std::vector<entity*>& getRenderableEntities() const { return renderableEntitiesCache; }
	const std::vector<entity*>& getRenderableTiles() const { return renderableTilesCache; }

	void addToRenderablesCache(entity* e, ENTITYTYPEENUM t);
	void removeFromRenderablesCache(entity* e, ENTITYTYPEENUM t);
	void updateRenderablesCache(ENTITYTYPEENUM t);
	void fullBuildRenderablesCache(ENTITYTYPEENUM t);
	void buildAllRenderablesCache();

	void addEntityToGame(std::string name, ENTITYTYPEENUM type);
	void removeEntityFromGame(int id);

	void updateView();
	const viewPort& getView() const { return view; }

private:
	int nextId = 0;

	viewPort view;
	std::vector<std::unique_ptr<entity>> entities;
	std::vector<entity*> renderableEntitiesCache; 
	std::vector<std::unique_ptr<entity>> tiles;
	std::vector<entity*> renderableTilesCache;
	std::vector<entity*> floorMap;
}; 