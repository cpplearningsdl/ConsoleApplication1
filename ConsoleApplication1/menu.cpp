#pragma once
#include "menu.h"
#include "menuManager.h"
 
void menuObj::setButtonActionData(std::vector<buttonObj>& buttons, const buttonsActionData data) {
	if (!buttons.empty()) {
		buttons.back().configureButton(data);  
	}
}


 