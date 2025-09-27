#pragma once
#include <string> 
#include <SDL3/SDL.h>
#include "inputManager.h"
#include "logManager.h"
#include "animationManager.h"
#include "entityRenderInfo.h"
#include "position.h"
#include "dimensions.h"
#include "buttonData.h"

  
class buttonObj {
private:
	position pos;
	dimensions size;
	bool render;
	std::string name;
	animationManager animationHandler;
	entityRenderInfo renderInfo;
	buttonsActionData butData;

public:
	buttonObj(position pos, dimensions sz, std::string newName, std::string animationName, bool visible ) : pos(pos), size(sz),  name(newName), render(visible) {
		animationHandler.setAnimationName(animationName);
		animationHandler.setEntityName(newName); 
		animationHandler.loadAnimation(animationName); 
		updateRenderInfo();
	}

	void configure(const buttonsActionData& newData) { butData = newData; }
	void loadAnimation(std::string s) { animationHandler.loadAnimation(s); }
	void setRender(bool b) { render = b; } 
	const position& getPos() const { return pos; }
	const dimensions& getSize() const { return size; }
	const entityRenderInfo& getEntityRenderInfo() const { return renderInfo; }
	void setMenuData(const buttonsActionData& data) { butData = data; }
	bool wasClicked() { return butData.clicked; }
	void setClicked(bool b) { butData.clicked = b; }
	buttonsActionData getButData() { return butData; }

	void update(inputManager& input) {	
		handleInput(input);
		animationHandler.step(); 
		updateRenderInfo();
	}
	void updateRenderInfo() {
		updateEntityRenderInfo(renderInfo, animationHandler.getCurrentTexture(), pos, animationHandler.getHeight(), animationHandler.getWidth(), render);
	}

	void handleInput(inputManager& input) { 
		if (input.wasMouseReleased() && contains(input.getMouseX(),input.getMouseY())) {
			click();
			logManager::logThis("Clicked button.");
		}
	 }
	bool contains(int mouseX, int mouseY) const {
		return mouseX >= pos.getX() && mouseX <= pos.getX() + size.getW() &&
			mouseY >= pos.getY() && mouseY <= pos.getY() + size.getH();
	}
	 
	void click() {
		butData.clicked = true;
	};
};
