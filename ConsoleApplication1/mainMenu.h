#pragma once
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

 