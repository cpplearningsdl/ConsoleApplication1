#pragma once
#include <vector>
#include <algorithm>
#include "logManager.h"
#include "menu.h"
#include "button.h"
#include "pauseMenu.h"
#include "inputManager.h"

class menuManager {
	std::vector<std::unique_ptr<menuObj>> menus;

public:

	void update(inputManager& input) {
		for (auto it = menus.rbegin(); it != menus.rend(); ++it) {
			if ((*it)->isVisible()) {
				(*it)->update(input);  
				if ((*it)->isModal()) break; 
			}
		}
	}

	const std::vector < std::unique_ptr<menuObj>>& getMenus() const {	return menus;	}

	void openMenu(std::unique_ptr<menuObj> menu) {
		if (menu->isModal()) { 
			for (auto& m : menus) {
				if (m->isModal()) m->hide();
			}
		}
		menu->show();
		menus.push_back(std::move(menu));
		logManager::logThis("opened window");
	}

	void closeTopMenu() {
		if (!menus.empty()) {
			menus.pop_back();  // removes and destroys the top menu
		}
	}
	void closeMenu(menuObj* menu) {
		menus.erase(std::remove_if(menus.begin(), menus.end(),
			[menu](const std::unique_ptr<menuObj>& m) { return m.get() == menu; }),
			menus.end());
	}

	void handleMouseClick(int mouseX, int mouseY) {
		// Topmost visible modal menu receives input first
		for (auto it = menus.rbegin(); it != menus.rend(); ++it) {
			if ((*it)->isVisible()) {
				(*it)->handleMouseClick(mouseX, mouseY);
				if ((*it)->isModal()) break; // block underlying menus/game
			}
		}
	}
 

	// Optional helper: check if a modal is active
	bool hasActiveModal() const {
		for (auto it = menus.rbegin(); it != menus.rend(); ++it) {
			if ((*it)->isVisible() && (*it)->isModal())
				return true;
		}
		return false;
	}
};
