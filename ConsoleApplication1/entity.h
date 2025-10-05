#pragma once
#include <string>  
#include "animationManager.h"
#include "abilities.h"
#include "statsContainer.h"
#include "position.h"
#include "abilityFactory.h"
#include "entityRenderInfo.h"
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
	const entityRenderInfo& getRenderInfo() const ; 

	std::string getName() const { return name; };
	void setName(std::string newName) {	name = newName;	};
	int getId() const { return entityId; }
	void setEntityId(int newId) { entityId = newId; };
	int getFactoryId() const { return factoryId; }
	void setFactoryId(int newId) { factoryId = newId; };
	void setRender(bool s) { render = s; renderInfo.render = s; }

	const bool&  getRender() const { return render; }
	
	movementPath& getPath() { return path; }

	const bool moving() const { return isMoving; }
	void setMoving(bool b) { isMoving = b; }

	const bool blockingMenus() const { return blockMenus; }
	void setBlockMenus(bool b) { blockMenus = b; }

	const statsContainer& getStats() const { return stats; }
	statsContainer& getStats() { return stats; }

	const position& getPos() const { return pos; }
	position& getPos() { return pos; }

	void setPos(position p) { pos = p; }

	//const position getCombinedPos() {
	//	logManager::logThis("pos: " + std::to_string(pos.getX()) + " " + std::to_string(pos.getY()));
	//	position movementPos = animationHandler.getPos();
	//	return { movementPos.getX() + pos.getX(), movementPos.getY() + pos.getY() };
	//}
	const position getCombinedPos() {
		position movementPos = animationHandler.getPos();
		position combinedPos{ movementPos.getX() + pos.getX(),
							  movementPos.getY() + pos.getY() };

		//logManager::logThis("pos: " + std::to_string(pos.getX()) + " " + std::to_string(pos.getY())		);

		//logManager::logThis("combinedPos: " + std::to_string(combinedPos.getX()) + " " + std::to_string(combinedPos.getY()));

		return combinedPos;
	}

	abilities& getAbilities();
	const abilities& getAbilities() const; 
	animationManager& getAnimationManager() { return animationHandler; }

	void updateRenderInfo();
	static nlohmann::ordered_json to_Json(const entity& e);
	void from_Json(const nlohmann::ordered_json& j);

	void spill_guts();
private:
	int entityId;
	int factoryId;
	position pos;
	bool render;
	bool blockMenus;
	bool isMoving;

	movementPath path;

	std::string name;
	statsContainer stats;
	abilities abilities; 
	
	animationManager animationHandler;
	entityRenderInfo renderInfo;
};
 