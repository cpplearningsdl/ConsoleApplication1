#pragma once
#include "position.h"
#include "dimensions.h"
#include "windowSettings.h"

struct viewPort {
	position viewPos{ 0, 0 };                  // top-left of camera in world coordinates
	dimensions mapSize{ 100, 100 };                // map dimensions in tiles
	dimensions tileSize{ 128, 128 };               // size of each tile in pixels
	dimensions screenSize{ logicalW, logicalH };   // logical screen size (default 800x600)

	position targetPos{ 0,0 };
	float speed = 0.0f;
	bool moving = false;
};

//grid x,y to array index
inline int gridToIndex(position& p, const viewPort& v) noexcept {
	return p.getY() * v.mapSize.getW() + p.getX();
}

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

// Convert world position -> grid coords (use center of entity)
inline position toGridCoords(const entity& e, const dimensions& tileSize) {
	// use combined pos + half of current frame size
	float cx = e.getCombinedPos().getX() + (e.getAnimationManager().getWidth() / 2.0f);
	float cy = e.getCombinedPos().getY() + (e.getAnimationManager().getHeight() / 2.0f);

	int gx = static_cast<int>(cx / tileSize.getW());
	int gy = static_cast<int>(cy / tileSize.getH());

	return position(gx, gy);
}

// Convert grid coords -> world pos (center of tile in world coords)
inline position fromGridCoords(const position& gridPos, const dimensions& tileSize) {
	float wx = (gridPos.getX() * tileSize.getW()) + tileSize.getW() / 2.0f;
	float wy = (gridPos.getY() * tileSize.getH()) + tileSize.getH() / 2.0f;

	return position(wx, wy);
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
	float camBottom = camTop + v.screenSize.getH();
	 
	// AABB overlap test
	return !(right < camLeft ||
		left > camRight ||
		bottom < camTop ||
		top > camBottom);
}

inline void setViewTarget(viewPort& v, const position& dest, float speed) {
	v.targetPos = dest;
	v.speed = speed;
	v.moving = true;
}

inline bool moveView(viewPort& v)
{
	if (!v.moving) return false; // already at target

	float dx = v.targetPos.getX() - v.viewPos.getX();
	float dy = v.targetPos.getY() - v.viewPos.getY();

	float distSq = dx * dx + dy * dy;
	float step = v.speed;

	if (distSq <= step * step)
	{
		v.viewPos = v.targetPos;
		v.moving = false;
		return false; // reached target, no more movement
	}
	else
	{
		float len = std::sqrt(distSq);
		v.viewPos.setX(v.viewPos.getX() + (dx / len) * step);
		v.viewPos.setY(v.viewPos.getY() + (dy / len) * step);
	}
	//clamp to map 
	float maxX = v.mapSize.getW() * v.tileSize.getW() - v.screenSize.getW();
	float maxY = v.mapSize.getH() * v.tileSize.getH() - v.screenSize.getH();

	if (v.viewPos.getX() < 0) v.viewPos.setX(0);
	if (v.viewPos.getY() < 0) v.viewPos.setY(0);
	if (v.viewPos.getX() > maxX) v.viewPos.setX(maxX);
	if (v.viewPos.getY() > maxY) v.viewPos.setY(maxY);

	return true; // still moving toward target
}

