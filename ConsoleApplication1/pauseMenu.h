#pragma once
#include "inputManager.h"
#include "menuManager.h"
#include "menu.h"
#include "button.h"
#include "buttonEnums.h"
#include "json.hpp"

class pauseMenu : public menuObj {
public:
	pauseMenu();
	void loadJson();
	void loadButtons();
	void init();
	void update(inputManager& input) override;
	void updateRenderInfo();

	friend void to_json(nlohmann::ordered_json& j, const pauseMenu& m);
	friend void from_json(const nlohmann::ordered_json& j, pauseMenu& m);
private:

};

inline void to_json(nlohmann::ordered_json& j, const pauseMenu& m) {
	to_json(j, static_cast<const menuObj&>(m));
//	j["extraValue"] = m.extraValue;
}

inline void from_json(const nlohmann::ordered_json& j, pauseMenu& m) {

	j.get_to(static_cast<menuObj&>(m));
}
