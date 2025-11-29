#pragma once
#include <vector>
#include "entityTypeEnum.h"
#include "view.h"
#include "turnContext.h"
#include "event.h"

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


private:
	std::vector<entity*> renderableEntityCache;
	std::vector<entity*> renderableTileCache;
};