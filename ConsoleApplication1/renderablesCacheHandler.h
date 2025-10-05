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
	position combinedPos = e->getCombinedPos();        // pos + animation offset
	dimensions size{ anim.getWidth(), anim.getHeight() }; // current frame size

	if (testInView(v, combinedPos, size)) {
		cache.push_back(e);
	}
}

// Remove an entity from the renderables cache by ID
inline void removeFromRenderables(std::vector<entity*>& cache, int id) {
	auto pit = std::remove_if(cache.begin(), cache.end(),
		[id](entity* e) { return e->getId() == id; });
	cache.erase(pit, cache.end());
}
