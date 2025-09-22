#pragma once
#include <string>
#include <functional>
#include "logManager.h"
#include "animationManager.h"
#include "entityRenderInfo.h"
#include "position.h"

 
//MAKE RESUME BUTTON ART ASSET
class buttonObj {
private:
	position pos;
	position size;
	bool render;
	std::string name;
	animationManager animationHandler;
	entityRenderInfo renderInfo;
public:
	buttonObj(position pos, position sz, std::function<void()> cb, std::string newName, std::string animationName, bool visible ) : pos(pos), size(sz), onClick(std::move(cb)), name(newName), render(visible) {
		animationHandler.setAnimationName(animationName);
		animationHandler.setEntityName(newName); 
		animationHandler.loadAnimation(animationName); 
		updateEntityRenderInfo(renderInfo, animationHandler.getTextureKey(), pos, render);
	}

	void loadAnimation(std::string s) { animationHandler.loadAnimation(s); }
	void setRender(bool b) { render = b; } 
	const position& getPos() const { return pos; }
	const position& getSize() const { return size; }

	void update() { 
		animationHandler.step(); 
		updateEntityRenderInfo(renderInfo, animationHandler.getTextureKey(), pos, render);
	}

	std::function<void()> onClick;
	 
	bool contains(int mouseX, int mouseY) const {
		return mouseX >= pos.getX() && mouseX <= pos.getX() + size.getX() &&
			mouseY >= pos.getY() && mouseY <= pos.getY() + size.getY();
	}
	 
	void click() {
		if (onClick) onClick();
		logManager::logThis("Clicked button.");
	}
};
