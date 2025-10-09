#pragma once
#include <vector> 
#include "entityIncludes.h"
#include "inputManager.h"
#include "level.h"
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

	void addEntityToGame(int factoryId, ENTITYTYPEENUM type);
	void addEntityToGame(int factoryId);
	void addEntityToGameFromJson(const std::string& jsonFilePath);

	void removeEntityFromGame(int id);

	void loadLevel(int l);
	void setLevelData(levelData&& d) noexcept { currentLevelData = std::move(d);}
	levelData& getLevelData() noexcept { return currentLevelData; }
	const levelData& getLevelData() const noexcept { return currentLevelData; }

	void updateView();
	const viewPort& getView() const { return view; }

private:
	int nextId = 0;

	levelData currentLevelData;
	viewPort view;
	std::vector<std::unique_ptr<entity>> entities;
	std::vector<entity*> renderableEntitiesCache; 
	std::vector<std::unique_ptr<entity>> tiles;
	std::vector<entity*> renderableTilesCache;
	std::vector<entity*> floorMap;
}; 