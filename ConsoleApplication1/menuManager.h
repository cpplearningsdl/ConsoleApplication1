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
	bool closed = false;

public:

	bool hasOpenWindow() const { return !menus.empty(); }
	void update(inputManager& input) {
		for (auto it = menus.rbegin(); it != menus.rend(); ++it) {
			if ((*it)->isVisible()) { 
				(*it)->update(input);
				if ((*it)->isModal()) break;
			} 
		} 

		for (auto it = menus.begin(); it != menus.end(); ) {
			if ((*it)->isPendingClose()) {
				menuObj* menu = it->get();   // get the raw pointer
				closeMenu(menu);             // pass pointer, as expected
				it = menus.begin();          // start over, safe
			}
			else {
				++it;
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
		menu->setParentMenu(this);
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
		logManager::logThis("closedwindow");
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
