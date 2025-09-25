#pragma once
#include "inputManager.h"
#include "menuManager.h"
#include "menu.h"
#include "button.h"
#include "json.hpp"

class pauseMenu : public menuObj {
public:
	pauseMenu();
	void loadJson();
	void loadButtons();
	void init();
	void update(inputManager& input) override;
	void updateRenderInfo();
	 
private:

};

inline void from_json(const nlohmann::ordered_json& j, menuObj& m) {
	if (j.contains("position")) {
		j.at("position").get_to(m.pos);
	}
	if (j.contains("renderInfo")) {
		j.at("renderInfo").get_to(m.renderInfo);
	}
	if (j.contains("animationHandler")) {
		j.at("animationHandler").get_to(m.animationHandler);
	}
	if (j.contains("render")) {
		m.show(); // if render is true
		if (!j.at("render").get<bool>()) {
			m.hide();
		}
	} 
}
