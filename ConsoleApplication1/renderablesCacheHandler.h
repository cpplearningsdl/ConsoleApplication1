#pragma once
#include <vector>
#include <algorithm>
#include "entity.h"
#include "position.h"
#include "dimensions.h"
#include "view.h" // for testInView

// Add an entity to the renderables cache if it's in view
inline void addToRenderables(std::vector<entity*>& cache, entity* e, const viewPort& v) {
	const animationManager& anim = e->getAnimationManager();
	position combinedPos = e->getCombinedPos();        // pos + animation offset//add vector to anim manager of the dimensions..
	dimensions size{ anim.getWidth(), anim.getHeight() }; // current frame size

	if (testInView(v, combinedPos, size)) {
		cache.push_back(e);
		logManager::logThis("added to renderables " + e->getName());
	}
}

// Remove an entity from the renderables cache by ID
inline void removeFromRenderables(std::vector<entity*>& cache, int id) {
	auto pit = std::remove_if(cache.begin(), cache.end(),
		[id](entity* e) {
		if (e->getId() == id) {
			logManager::logThis("Removed entity from renderables: " + e->getAnimationManager().getEntityName());
			return true;
		}
		return false;
	}); 
	cache.erase(pit, cache.end());
}

// Remove any entities that are outside the current view
//H/W are in their own arrays in animation manager so thats why return by value
//consider adding container of the size obj version
inline void pruneRenderables(std::vector<entity*>& cache, const viewPort& v) {
	auto it = std::remove_if(cache.begin(), cache.end(),
		[&v](entity* e) {
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

inline void generateRenderablesCache(const std::vector<std::unique_ptr<entity>>& entities, std::vector<entity*>& cache, const viewPort& v) {
	cache.clear();
	cache.reserve(entities.size()); // optional optimization

	for (const auto& e : entities)
	{
		if (!e) continue;

		const position& pos = e->getCombinedPos();
		dimensions size(e->getAnimationManager().getWidth(),
			e->getAnimationManager().getHeight());

		if (testInView(v, pos, size))
			cache.push_back(e.get());
	}
}
//use 1d array for lookups on floor tiles instead of testing every floor
inline void generateTileRenderablesCache( const std::vector<entity*>& tileMap, std::vector<entity*>& cache, const viewPort& v, int mapWidth, int mapHeight){
	cache.clear();

	int startCol = std::max(0, static_cast<int>(v.viewPos.getX() / v.tileSize.getW()) - 1);
	int startRow = std::max(0, static_cast<int>(v.viewPos.getY() / v.tileSize.getH()) - 1);

	int endCol = std::min(mapWidth - 1, static_cast<int>((v.viewPos.getX() + v.screenSize.getW()) / v.tileSize.getW()) + 1);
	int endRow = std::min(mapHeight - 1, static_cast<int>((v.viewPos.getY() + v.screenSize.getH()) / v.tileSize.getH()) + 1);

	for (int row = startRow; row <= endRow; ++row)
	{
		for (int col = startCol; col <= endCol; ++col)
		{
			int index = row * mapWidth + col;
			entity* tile = tileMap[index];
			if (tile)
				cache.push_back(tile);
		}
	}
}