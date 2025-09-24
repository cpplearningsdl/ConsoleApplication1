#pragma once
#include <string>
#include <functional>
#include "logManager.h"
#include "animationManager.h"
#include "entityRenderInfo.h"
#include "position.h"
#include "dimensions.h"

  
class buttonObj {
private:
	position pos;
	dimensions size;
	bool render;
	std::string name;
	animationManager animationHandler;
	entityRenderInfo renderInfo;
public:
	buttonObj(position pos, dimensions sz, std::function<void()> cb, std::string newName, std::string animationName, bool visible ) : pos(pos), size(sz), onClick(std::move(cb)), name(newName), render(visible) {
		animationHandler.setAnimationName(animationName);
		animationHandler.setEntityName(newName); 
		animationHandler.loadAnimation(animationName); 
		updateRenderInfo();
	}

	void loadAnimation(std::string s) { animationHandler.loadAnimation(s); }
	void setRender(bool b) { render = b; } 
	const position& getPos() const { return pos; }
	const dimensions& getSize() const { return size; }
	const entityRenderInfo& getEntityRenderInfo() const { return renderInfo; }

	void update() { 
		animationHandler.step(); 
		updateRenderInfo();
	}
	void updateRenderInfo() {
		updateEntityRenderInfo(renderInfo, animationHandler.getCurrentTexture(), pos, animationHandler.getHeight(), animationHandler.getWidth(), render);
	}
	std::function<void()> onClick;
	 
	bool contains(int mouseX, int mouseY) const {
		return mouseX >= pos.getX() && mouseX <= pos.getX() + size.getW() &&
			mouseY >= pos.getY() && mouseY <= pos.getY() + size.getH();
	}
	 
	void click() {
		if (onClick) onClick();
		logManager::logThis("Clicked button.");
	}
};
