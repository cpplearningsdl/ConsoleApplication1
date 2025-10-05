#pragma once
#include "position.h"
#include "dimensions.h"

struct viewPort {
	position viewPos;                  // top-left of camera in world coordinates
	dimensions mapSize;                // map dimensions in tiles
	dimensions tileSize;               // size of each tile in pixels
	dimensions screenSize{ 800, 600 };   // logical screen size (default 800x600)
};

// Convert from world coords to grid coords (tile index position)
inline position toGridCoords(const position& p, const viewPort& v) {
	return position{
		p.getX() / v.tileSize.getW(),
		p.getY() / v.tileSize.getH()
	};
}

// Convert from grid coords back to world coords (top-left pixel of that tile)
inline position toWorldCoords(const position& gridPos, const viewPort& v) {
	return position{
		gridPos.getX() * v.tileSize.getW(),
		gridPos.getY() * v.tileSize.getH()
	};
}

// Check if an entity at world position `p` with size `s` is visible in the viewport
inline bool testInView(const viewPort& v, const position& p, const dimensions& s) {
	// entity bounds
	float left = p.getX();
	float right = p.getX() + s.getW();
	float top = p.getY();
	float bottom = p.getY() + s.getH();

	// camera bounds
	float camLeft = v.viewPos.getX();
	float camTop = v.viewPos.getY();
	float camRight = camLeft + v.screenSize.getW();
	float	 camBottom = camTop + v.screenSize.getH();

	// AABB overlap test
	return !(right < camLeft ||
		left > camRight ||
		bottom < camTop ||
		top > camBottom);
}
