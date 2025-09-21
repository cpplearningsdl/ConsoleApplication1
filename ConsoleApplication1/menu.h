#pragma once
#include <vector>
#include "button.h"
#include "logManager.h"
#include "animationManager.h"
#include "entityRenderInfo.h"

class menuObj { 
protected:
	std::vector<buttonObj> buttons;
	bool render = false;
	bool modal = false;
	animationManager animationHandler;
	entityRenderInfo renderInfo;
	position pos;

public:
	virtual ~menuObj() = default;

	virtual void update() {};
	void show() { render = true; }
	void hide() { render = false; }
	bool isVisible() const { return render; }

	void setModal(bool m) { modal = m; }
	bool isModal() const { return modal; }

	// Handle mouse clicks
	void handleMouseClick(int mouseX, int mouseY) {
		if (!render) return;
		for (auto& btn : buttons) {
			if (btn.contains(mouseX, mouseY)) {
				btn.click();
				break;
			}
		}
	}  

	friend void from_json(const nlohmann::ordered_json& j, menuObj& m);
};
