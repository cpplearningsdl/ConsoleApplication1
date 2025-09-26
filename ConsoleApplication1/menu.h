#pragma once
#include <vector>
#include "button.h"
#include "defaultButtonSettings.h"
#include "logManager.h"
#include "animationManager.h"
#include "entityRenderInfo.h"
#include "inputManager.h"

class menuManager;

class menuObj { 
protected:
	menuManager* parentMenu = nullptr;
	std::vector<buttonObj> buttons;
	std::vector<buttonsActionData> clickedButtons;

	bool render = false;
	bool modal = false;
	bool pendingClose = false;

	animationManager animationHandler;
	entityRenderInfo renderInfo;
	position pos;

public:
	virtual ~menuObj() = default;

	void setParentMenu(menuManager* m) { parentMenu = m; }
	virtual void update(inputManager& input) = 0;
	void show() { render = true; }
	void hide() { render = false; }
	bool isVisible() const { return render; } 
	void setModal(bool m) { modal = m; }
	bool isModal() const { return modal; } 
	bool getRender() const { return render; }
	bool isPendingClose() const { return pendingClose; }


	void requestClose() { pendingClose = true; }

	const entityRenderInfo & getEntityRenderInfo() const { return renderInfo; }
	const std::vector<buttonObj>& getButtons() const { return buttons; }
	  
	void setButtonMenuData(std::vector<buttonObj>& buttons, const buttonsActionData data); 

	// Handle mouse clicks
	//void handleMouseClick(int mouseX, int mouseY) {
	//	if (!render) return;
	//	for (auto& btn : buttons) {
	//		if (btn.contains(mouseX, mouseY)) {
	//			btn.click();
	//			break;
	//		}
	//	}
	//}  

	friend void from_json(const nlohmann::ordered_json& j, menuObj& m);
};
