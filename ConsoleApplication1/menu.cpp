#pragma once
#include "menu.h"
#include "menuManager.h"
 
void menuObj::setButtonMenuData(std::vector<buttonObj>& buttons, const buttonsActionData data) {
	if (!buttons.empty()) {
		buttons.back().setMenuData(data);  
	}
}

 