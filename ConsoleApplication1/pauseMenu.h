#pragma once
#include "inputManager.h"
#include "menuManager.h"
#include "menu.h"
#include "button.h"
#include "buttonEnums.h"
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

inline void from_json(const nlohmann::ordered_json& j, pauseMenu& m) {

	j.get_to(static_cast<menuObj&>(m));
}
