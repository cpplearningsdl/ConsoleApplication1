#pragma once
#include <vector>
#include "entityTypeEnum.h"
#include "view.h"
#include "turnContext.h"
#include "GameEvent.h"

class entity; 

class renderCacheManager {

public: 
	renderCacheManager();
	~renderCacheManager();

	const std::vector<entity*>& getRenderableEntities() const { return renderableEntityCache; }
	const std::vector<entity*>& getRenderableTiles() const { return renderableTileCache; }

	void addToRenderablesCache(entity* e, const viewPort& view);
	void removeFromRenderablesCache(entity* e); 
	void removeFromRenderablesById(int id);
	void generateEntityRenderablesCache(const viewPort& v, std::vector<std::unique_ptr<entity>>& entities);
	void generateTileRenderablesCache(const viewPort& v, std::vector<entity*>& floorMap);
	void pruneRenderables(std::vector<entity*>& cache, const viewPort& v, ENTITYTYPEENUM type);

	void processEvent(turnContext& ctx, const gameEvent& event);
	void executeEvent(turnContext& ctx, const gameEvent& event);
private:
	std::vector<entity*> renderableEntityCache;
	std::vector<entity*> renderableTileCache;
};