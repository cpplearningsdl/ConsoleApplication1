#pragma once
#include "position.h"
#include "dimensions.h"
#include "windowSettings.h"
#include "entity.h"

struct viewPort {
	position viewPos{ 0, 0 };                  // top-left of camera in world coordinates
	dimensions mapSize{ 100, 100 };                // map dimensions in tiles
	dimensions tileSize{ 128, 128 };               // size of each tile in pixels
	dimensions screenSize{ logicalW, logicalH };   // logical screen size  

	position targetPos{ 0,0 };
	float speed = 0.0f;
	bool moving = false;
	bool rotating = false;          // true if the camera is currently orbiting
	float angle = 1.0f;             // current angle of rotation (radians)
	float radius = 256.0f;          // distance from target point for orbit
	float targetRadius = 0.0f;
	float radiusStep = 0.0f;
	bool increaseRadius = false;
	bool oscilate = false;
	float angularSpeed = 0.03f;     // radians per update

  
	static constexpr float PI = 3.14159265358979323846f;
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
	v.rotating = false;
	v.targetPos = dest;
	v.speed = speed;
	v.moving = true;
}

inline bool moveView(viewPort& v)
{
	if (!v.moving) return false;

	const float halfW = v.screenSize.getW() / 2.0f;
	const float halfH = v.screenSize.getH() / 2.0f;

	// current center of camera in world coords
	const float centerX = v.viewPos.getX() + halfW;
	const float centerY = v.viewPos.getY() + halfH;

	// vector from center to target (target is world-space point we want centered)
	const float dx = v.targetPos.getX() - centerX;
	const float dy = v.targetPos.getY() - centerY;

	const float distSq = dx * dx + dy * dy;
	const float step = v.speed;

	// if center is within one step of the target, snap center to target
	if (distSq <= step * step)
	{
		v.viewPos.setX(v.targetPos.getX() - halfW);
		v.viewPos.setY(v.targetPos.getY() - halfH);
		v.moving = false;
		return false; // reached target, no more movement
	}

	// otherwise move the camera center toward the target by 'step'
	const float len = std::sqrt(distSq);
	const float moveX = (dx / len) * step;
	const float moveY = (dy / len) * step;

	v.viewPos.setX(v.viewPos.getX() + moveX);
	v.viewPos.setY(v.viewPos.getY() + moveY);

	//// clamp top-left to map bounds (so viewPos stays valid)
	//const float maxX = v.mapSize.getW() * v.tileSize.getW() - v.screenSize.getW();
	//const float maxY = v.mapSize.getH() * v.tileSize.getH() - v.screenSize.getH();

	//if (v.viewPos.getX() < 0) v.viewPos.setX(0);
	//if (v.viewPos.getY() < 0) v.viewPos.setY(0);
	//if (v.viewPos.getX() > maxX) v.viewPos.setX(maxX);
	//if (v.viewPos.getY() > maxY) v.viewPos.setY(maxY);

	return true; // still moving
}


inline void startRotation(viewPort& v, const position& center, float startRadius, float targetRad, float speedRadiansPerFrame, bool osc, float rSpeed) {
	v.moving = false;
	v.targetPos = center;
	v.radius = startRadius;
	v.targetRadius = targetRad;
	v.radiusStep = rSpeed;
	v.oscilate = osc;
	v.angularSpeed = speedRadiansPerFrame;
	v.rotating = true;
	v.increaseRadius = true;
}

inline void stopRotation(viewPort& v) {
	v.rotating = false;
}

inline void updateRotation(viewPort& v) {
	if (!v.rotating) return;

	if (v.increaseRadius)
	{
		v.radius += v.radiusStep;
		if (v.radius >= v.targetRadius)
		{
			v.radius = v.targetRadius;
			v.increaseRadius = false; // stop increasing (or flip if you want oscillation)
		}
	}
	else
	{
		if (v.oscilate) {
			v.radius -= v.radiusStep;
			if (v.radius <= 0) { v.increaseRadius = true; }
		}
	}
	// --- advance angle ---
	v.angle += v.angularSpeed;
	if (v.angle > 2 * v.PI) v.angle -= 2 * v.PI;
	  
	// --- orbit around target ---
	float cosA = cosf(v.angle);
	float sinA = sinf(v.angle);

	float targetX = v.targetPos.getX() + cosA * v.radius;
	float targetY = v.targetPos.getY() + sinA * v.radius;

	// --- center camera on orbit position ---
	float halfW = v.screenSize.getW() / 2.0f;
	float halfH = v.screenSize.getH() / 2.0f;

	v.viewPos.setX(targetX - halfW);
	v.viewPos.setY(targetY - halfH);
 
}
