#pragma once
#include <vector>
#include <algorithm>
#include "logManager.h"
#include "menu.h"
#include "button.h"
#include "pauseMenu.h"

class menuManager {
	std::vector<std::unique_ptr<menuObj>> menus;

public:
	void openMenu(std::unique_ptr<menuObj> menu) {
		if (menu->isModal()) {
			// Hide other modals
			for (auto& m : menus) {
				if (m->isModal()) m->hide();
			}
		}
		menu->show();
		menus.push_back(std::move(menu));
		logManager::logThis("opened window");
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
