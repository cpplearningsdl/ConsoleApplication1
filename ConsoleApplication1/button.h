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
	buttonObj() {};
	buttonObj(position pos, dimensions sz, std::string newName, std::string animationName, bool visible ) : pos(pos), size(sz),  name(newName), render(visible) {
		animationHandler.setAnimationName(animationName);
		animationHandler.setEntityName(newName); 
		animationHandler.loadAnimation(animationName); 
		updateRenderInfo();
	}

	void configureButton(const buttonsActionData& newData) { butData = newData; }
	void loadAnimation(std::string s) { animationHandler.loadAnimation(s); }
	void setRender(bool b) { render = b; } 
	const position& getPos() const { return pos; }
	const dimensions& getSize() const { return size; }
	const entityRenderInfo& getEntityRenderInfo() const { return renderInfo; } 
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
	friend void to_json(nlohmann::ordered_json& j, const buttonObj& b);
	friend void from_json(const nlohmann::ordered_json& j, buttonObj& b);

};

inline void buttonSpillGuts(buttonObj& b) {
	nlohmann::ordered_json j;  
	to_json(j, b);
	logManager::logThis(j.dump(4));
}

// ---------------------- TO JSON ----------------------
inline void to_json(nlohmann::ordered_json& j, const buttonObj& b) {
	j = nlohmann::ordered_json{
		{"position", b.pos},
		{"size", b.size},
		{"render", b.render},
		{"name", b.name},
		{"animationHandler", b.animationHandler},
		{"renderInfo", b.renderInfo},
		{"buttonData", b.butData}
	};
}

// ---------------------- FROM JSON ----------------------
inline void from_json(const nlohmann::ordered_json& j, buttonObj& b) {
	j.at("position").get_to(b.pos);
	j.at("size").get_to(b.size);
	j.at("render").get_to(b.render);
	j.at("name").get_to(b.name);
	j.at("animationHandler").get_to(b.animationHandler);
	j.at("renderInfo").get_to(b.renderInfo);
	j.at("buttonData").get_to(b.butData);
}