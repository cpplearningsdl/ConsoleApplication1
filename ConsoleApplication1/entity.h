#pragma once
#include <string>  
#include "interactability.h"
#include "animationManager.h"
#include "abilities.h"
#include "statsContainer.h"
#include "position.h"
#include "abilityFactory.h"
#include "entityRenderInfo.h"
#include "entityTypeEnum.h"
#include "characterTypeEnum.h"
#include "json.hpp"

//should probably make a member of this and update it manually instead of polling every frame..
//porbably should move this to animationHandler as well..


class entity {
public:
	entity();
	~entity() = default;

	// Deep copy constructor
	entity(const entity& other); 
	// Deep copy assignment
	entity& operator=(const entity& other); 
	// Move semantics
	entity(entity&&) noexcept = default;
	entity& operator=(entity&&) noexcept = default;

	void update(); 
	void updateRenderInfo();
	const entityRenderInfo getRenderInfo(); 

	std::string getName() const { return name; };
	void setName(std::string newName) {	name = newName;	};
	void setCharacterType(CHARACTERTYPEENUM t) { charType = t;}
	const CHARACTERTYPEENUM getCharacterType() const { return charType; };
	void setType(ENTITYTYPEENUM t) { type = t; };
	const ENTITYTYPEENUM getType() const { return type; };
	bool isType(ENTITYTYPEENUM t) const noexcept { return type == t; };
	int getId() const { return entityId; };
	void setEntityId(int newId) { entityId = newId; };
	int getFactoryId() const { return factoryId; };
	void setFactoryId(int newId) { factoryId = newId; };
	void setRender(bool s) { render = s; renderInfo.render = s; };
	void setAlive(bool a) { alive = a; };
	const bool isAlive() const { return alive; };
	void kill(bool k) { alive = false; };

	const bool&  getRender() const { return render; }
	
	movementPath& getPath() { return path; }

	const bool moving() const { return isMoving; }
	void setMoving(bool b) { isMoving = b; }

	const bool blockingMenus() const { return blockMenus; }
	void setBlockMenus(bool b) { blockMenus = b; }
	const bool unblockMenu() const { return unblockMenus; };
	void setUnblockMenu(bool b) { unblockMenus = b; }

	const statsContainer& getStats() const { return stats; }
	statsContainer& getStats() { return stats; }

	const position& getPos() const { return pos; }
	position& getPos() { return pos; }
	void setPos(position p) { pos = p;}

	const position getCombinedPos() {
		position movementPos = animationHandler.getPos();
		position combinedPos{ movementPos.getX() + pos.getX(), movementPos.getY() + pos.getY() }; 
		return combinedPos;
	}
	const position getCombinedPos() const {
		position movementPos = animationHandler.getPos();
		position combinedPos{ movementPos.getX() + pos.getX(), movementPos.getY() + pos.getY() };
		return combinedPos;
	}

	abilities& getAbilities();
	const abilities& getAbilities() const; 
	animationManager& getAnimationManager() { return animationHandler; }
	const animationManager& getAnimationManager() const { return animationHandler; }
	 
	static nlohmann::ordered_json to_Json(const entity& e);
	void from_Json(const nlohmann::ordered_json& j);

	void spill_guts();
	void spill_guts(std::string s); 
private:
	ENTITYTYPEENUM type;
	CHARACTERTYPEENUM charType;
	std::string name;
	int entityId;
	int factoryId;
	position pos;
	bool alive;
	bool render;
	bool blockMenus;
	bool unblockMenus;
	bool isMoving;

	movementPath path; 
	InteractFlags interactions;
	statsContainer stats;
	abilities abilities; 
	
	
	animationManager animationHandler;
	entityRenderInfo renderInfo;
};
 