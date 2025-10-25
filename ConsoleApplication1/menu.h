#pragma once
#include <vector>
#include "button.h"
#include "buttonEnums.h"
#include "defaultButtonSettings.h"
#include "windowSettings.h"
#include "logManager.h"
#include "animationManager.h"
#include "entityRenderInfo.h"
#include "inputManager.h"

class menuManager;

class menuObj { 
protected:
	menuManager* parentMenu = nullptr;
	std::vector<buttonObj> buttons;
	std::vector<buttonsActionData> clickedButtons;

	bool render = false;
	bool modal = false;
	bool pendingClose = false;

	animationManager animationHandler;
	entityRenderInfo renderInfo;
	position pos;

public:
	virtual ~menuObj() = default;

	void setParentMenu(menuManager* m) { parentMenu = m; }
	virtual void update(inputManager& input) = 0;
	void show() { render = true; }
	void hide() { render = false; }
	bool isVisible() const { return render; } 
	void setModal(bool m) { modal = m; }
	bool isModal() const { return modal; } 
	bool getRender() const { return render; }
	bool isPendingClose() const { return pendingClose; }


	void requestClose() { pendingClose = true; }

	const animationManager& getAnimationManager() const { return animationHandler; }
	const entityRenderInfo & getEntityRenderInfo() const { return renderInfo; }
	const std::vector<buttonObj>& getButtons() const { return buttons; }
	  
	void setButtonActionData(std::vector<buttonObj>& buttons, const buttonsActionData data); 

 

	friend void from_json(const nlohmann::ordered_json& j, menuObj& m); 
	friend void to_json(nlohmann::ordered_json& j, const menuObj& m);
};
 
inline void from_json(const nlohmann::ordered_json& j, menuObj& m) {
	// --- buttons ---
	if (j.contains("buttons")) {
		m.buttons.clear();
		for (const auto& el : j.at("buttons")) {
			buttonObj b;
			from_json(el, b);  // explicit call to buttonObj's from_json
			m.buttons.push_back(std::move(b));
		}
	}

	// --- clickedButtons ---
	if (j.contains("clickedButtons")) {
		m.clickedButtons.clear();
		for (const auto& el : j.at("clickedButtons")) {
			buttonsActionData d;
			from_json(el, d);  // explicit call to BAD's from_json
			m.clickedButtons.push_back(std::move(d));
		}
	}

	// --- simple members ---
	if (j.contains("render")) m.render = j.at("render").get<bool>();
	if (j.contains("modal")) m.modal = j.at("modal").get<bool>();
	if (j.contains("pendingClose")) m.pendingClose = j.at("pendingClose").get<bool>();

	// --- custom classes ---
	if (j.contains("animationHandler")) from_json(j.at("animationHandler"), m.animationHandler);
	if (j.contains("renderInfo")) from_json(j.at("renderInfo"), m.renderInfo);
	if (j.contains("position")) from_json(j.at("position"), m.pos);
}
inline void to_json(nlohmann::ordered_json& j, const menuObj& m) {
	j = nlohmann::ordered_json{  
		{"render", m.getRender()},
		{"modal", m.isModal()},
		{"pendingClose", m.isPendingClose()},
		{"animationHandler", m.animationHandler},
		{"renderInfo", m.getEntityRenderInfo()},
		{"pos", m.pos},
		{"buttons", m.getButtons()},
		{"clickedButtons", m.clickedButtons}
	};
}