#pragma once
#include <string>
#include <functional>
#include "logManager.h"


struct Vec2 { int x, y; };

class buttonObj {
public:
	Vec2 position;
	Vec2 size;
	std::string label; 
	std::function<void()> onClick;

	buttonObj(Vec2 pos, Vec2 sz, std::function<void()> cb, std::string lbl = "") : position(pos), size(sz), onClick(std::move(cb)), label(lbl) {}

	bool contains(int mouseX, int mouseY) const {
		return mouseX >= position.x && mouseX <= position.x + size.x &&
			mouseY >= position.y && mouseY <= position.y + size.y;
	}

  
	void click() {
		if (onClick) onClick();
		logManager::logThis("Clicked button.");
	}
};
