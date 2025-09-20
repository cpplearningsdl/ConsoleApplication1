#pragma once
#include "menuManager.h"
#include "menu.h"
#include "button.h"

class pauseMenu : public menuObj {
public:
	pauseMenu(menuManager& uiMgr) { setModal(true);

		buttons.emplace_back(
			Vec2{ 100, 100 }, Vec2{ 200, 50 },
			[&]() {  hide(); },
			"Resume"
		);

		buttons.emplace_back(
			Vec2{ 100, 200 }, Vec2{ 200, 50 },
			[&]() {  },
			"Save"
		);

		buttons.emplace_back(
			Vec2{ 100, 300 }, Vec2{ 200, 50 },
			[&]() {  },
			"Quit"
		);
	}
};
