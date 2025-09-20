#pragma once
#include <vector>
#include "button.h"
#include "logManager.h"


class menuObj { 
protected:
	std::vector<buttonObj> buttons;
	bool visible = false;
	bool modal = false;

public:
	virtual ~menuObj() = default;

	void show() { visible = true; }
	void hide() { visible = false; }
	bool isVisible() const { return visible; }

	void setModal(bool m) { modal = m; }
	bool isModal() const { return modal; }

	// Handle mouse clicks
	void handleMouseClick(int mouseX, int mouseY) {
		if (!visible) return;
		for (auto& btn : buttons) {
			if (btn.contains(mouseX, mouseY)) {
				btn.click();
				break;
			}
		}
	}

 
};
