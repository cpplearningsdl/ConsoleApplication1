#pragma once
#include "drop.h"

void drop::update(float dt) {
	start.x += velocity.x * dt;
	start.y += velocity.y * dt;

	end.x += velocity.x * dt;
	end.y += velocity.y * dt;
}