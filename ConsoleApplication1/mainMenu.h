#pragma once 
#include "inputManager.h"
#include "menuManager.h"
#include "menu.h"
#include "button.h"
#include "buttonEnums.h"
#include "json.hpp"

class mainMenu : public menuObj {
public:
	mainMenu();
	void loadJson();
	void loadButtons();
	void init();
	void update(inputManager& input) override;
	void updateRenderInfo();


private:

};

inline void from_json(const nlohmann::ordered_json& j, mainMenu& m) {
	j.get_to(static_cast<menuObj&>(m));

}
