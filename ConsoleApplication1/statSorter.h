#pragma once
#include <vector>
#include "statClass.h"
#include "statEnum.h"
#include "entity.h"

inline void sortIdByStatBiggestLast(statEnum s, std::vector<entity*>& entities, std::vector<entity*>& tiles, std::vector<int>& ids) {
	// Quick lookup tables
	std::unordered_map<int, entity*> entityMap;
	std::unordered_map<int, entity*> tileMap;

	entityMap.reserve(entities.size());
	tileMap.reserve(tiles.size());

	for (auto* e : entities)
		if (e) entityMap[e->getId()] = e;

	for (auto* t : tiles)
		if (t) tileMap[t->getId()] = t;

	auto getStatValue = [&](int id) -> float {
		// Look for entity
		if (auto it = entityMap.find(id); it != entityMap.end()) {
			const statsContainer& sc = it->second->getStats();
			if (sc.hasStat(s))
				return sc.get(s).getCurrent();
			return -FLT_MAX;
		}

		// Look for tile
		if (auto it = tileMap.find(id); it != tileMap.end()) {
			const statsContainer& sc = it->second->getStats();
			if (sc.hasStat(s))
				return sc.get(s).getCurrent();
			return -FLT_MAX;
		}

		// Not found or missing stat
		return -FLT_MAX;
	};

	// Sort so highest stat value ends up at .back()
	std::sort(ids.begin(), ids.end(), [&](int a, int b) {
		return getStatValue(a) < getStatValue(b);
	});
}
