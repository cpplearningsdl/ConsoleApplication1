#pragma once
#include "renderCacheManager.h"
#include "view.h"
#include "entity.h"

renderCacheManager::renderCacheManager() {

}
renderCacheManager::~renderCacheManager() {

}

void renderCacheManager::addToRenderablesCache(entity* e, const viewPort& view) {
	ENTITYTYPEENUM t = e->getType();
	if (t == TILE) {
		if (testInView(view, e->getCombinedPos(), { e->getAnimationManager().getHeight(),  e->getAnimationManager().getWidth() })) {
			renderableTileCache.push_back(e);
			//logManager::logThis("Added entity to rendercache: ", e->getName());
		}
		return;
	}
	else if (t == ENTITY){
		if (testInView(view, e->getCombinedPos(), { e->getAnimationManager().getHeight(),  e->getAnimationManager().getWidth() })) {
			renderableEntityCache.push_back(e);
			//logManager::logThis("Added entity to rendercache: ", e->getName());
		}
		return;
	}
	logManager::logThis("Couldn't add to renderables cache: unknown type: ", t);
}
void renderCacheManager::removeFromRenderablesCache(entity* e) {
	if (!e) return;
	ENTITYTYPEENUM t = e->getType();
	std::vector<entity*>* targetCache = nullptr;

	if (t == TILE) {
		targetCache = &renderableTileCache;
	}
	else if (t ==ENTITY){
		targetCache = &renderableEntityCache;
	}

	auto& cache = *targetCache;
	auto it = std::find(cache.begin(), cache.end(), e);
	if (it != cache.end()) {
		cache.erase(it);
		logManager::logThis("Removed from render cache: ", e->getName());
	}
 
}
  
void renderCacheManager::removeFromRenderablesById(int id) {
	auto removeById = [id](std::vector<entity*>& cache) {
		auto it = std::find_if(cache.begin(), cache.end(),
			[id](entity* e) { return e && e->getId() == id; });

		if (it != cache.end()) {
			logManager::logThis("Removed from render cache: ", (*it)->getName());
			cache.erase(it);
		}
	};

	removeById(renderableEntityCache);
	removeById(renderableTileCache);
}
  
void renderCacheManager::pruneRenderables(std::vector<entity*>& cache, const viewPort& v, ENTITYTYPEENUM type){
	if (type == TILE) {
		// Compute min/max tile indices visible in the viewport
		int minX = std::max(0, static_cast<int>(v.viewPos.getX() / v.tileSize.getW()));
		int maxX = std::min(v.mapSize.getW() - 1,
			static_cast<int>((v.viewPos.getX() + v.screenSize.getW()) / v.tileSize.getW()));
		int minY = std::max(0, static_cast<int>(v.viewPos.getY() / v.tileSize.getH()));
		int maxY = std::min(v.mapSize.getH() - 1,
			static_cast<int>((v.viewPos.getY() + v.screenSize.getH()) / v.tileSize.getH()));

		auto it = std::remove_if(cache.begin(), cache.end(), [&](entity* e) {

			const position& pos = e->getCombinedPos();
			int tileX = static_cast<int>(pos.getX() / v.tileSize.getW());
			int tileY = static_cast<int>(pos.getY() / v.tileSize.getH());

			bool inView = (tileX >= minX && tileX <= maxX && tileY >= minY && tileY <= maxY);

			if (!inView) {
				logManager::logThis("Pruned tile: " + e->getAnimationManager().getEntityName());
			}

			return !inView; // remove if not in view
		});

		cache.erase(it, cache.end());
	}
	else {
		// Standard pruning for non-tile entities
		auto it = std::remove_if(cache.begin(), cache.end(),
			[&](entity* e) {
			const position& pos = e->getCombinedPos();
			dimensions size(e->getAnimationManager().getWidth(),
				e->getAnimationManager().getHeight());

			bool inView = testInView(v, pos, size);

			if (!inView) {
				logManager::logThis("Pruned entity: " + e->getAnimationManager().getEntityName());
			}

			return !inView; // remove if not in view
		});

		cache.erase(it, cache.end());
	}
}



void renderCacheManager::generateEntityRenderablesCache(const viewPort& v, std::vector<std::unique_ptr<entity>>& entities) {
	renderableEntityCache.clear();
	renderableEntityCache.reserve(entities.size()); // optional optimization

	for (const auto& e : entities)
	{
		if (!e) continue;

		const position& pos = e->getCombinedPos();
		dimensions size(e->getAnimationManager().getWidth(),
			e->getAnimationManager().getHeight());

		if (testInView(v, pos, size))
			renderableEntityCache.push_back(e.get());
	}
}
//use 1d array for lookups on floor tiles instead of testing every floor
void renderCacheManager::generateTileRenderablesCache(const viewPort& v, std::vector<entity*>& tileMap) {
	renderableTileCache.clear();

	int startCol = std::max(0, static_cast<int>(v.viewPos.getX() / v.tileSize.getW()) - 1);
	int startRow = std::max(0, static_cast<int>(v.viewPos.getY() / v.tileSize.getH()) - 1);

	int endCol = std::min(v.mapSize.getW() - 1, static_cast<int>((v.viewPos.getX() + v.screenSize.getW()) / v.tileSize.getW()) + 1);
	int endRow = std::min(v.mapSize.getH() - 1, static_cast<int>((v.viewPos.getY() + v.screenSize.getH()) / v.tileSize.getH()) + 1);

	//logManager::logThis("generateTileRenderablesCache view indices: ["+ std::to_string(startCol) + "][" + std::to_string(startRow) + "]-["+ std::to_string(endCol) + "][" + std::to_string(endRow) + "]");
	for (int row = startRow; row <= endRow; ++row)
	{
		for (int col = startCol; col <= endCol; ++col)
		{
			int index = row * v.mapSize.getW() + col;
			entity* tile = tileMap[index];
			if (tile)
				renderableTileCache.push_back(tile);
		}
	}
}