#pragma once
#include <vector>
#include "button.h"
#include "logManager.h"
#include "animationManager.h"
#include "entityRenderInfo.h"
#include "inputManager.h"

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

	virtual void update(inputManager& input) = 0;
	void show() { render = true; }
	void hide() { render = false; }
	bool isVisible() const { return render; } 
	void setModal(bool m) { modal = m; }
	bool isModal() const { return modal; } 

	const entityRenderInfo & getEntityRenderInfo() const { return renderInfo; }
	const std::vector<buttonObj>& getButtons() const { return buttons; }

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
