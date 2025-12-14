
#include "entity.h"
#include "json.hpp"
//using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

entity::entity() {

}
//WHEN ADDING NEW MEMBERS TO ENTITY ADD TO THE CONSTRUCTORS IDIOT NOT JUST JSON
entity::entity(const entity& other)
	: animationHandler(other.animationHandler) // uses deep copy from animationManager
{
	entityId = other.entityId;
	factoryId = other.factoryId;
	name = other.name;
	type = other.type;
	charType = other.charType;
	stats = other.stats;
	abilities = other.abilities;  
	interactions = other.interactions;
	alive = other.alive;
	animationHandler.setEntityName(name);
	render = other.render;
	renderInfo = other.renderInfo;
}

entity& entity::operator=(const entity& other) {
	if (this != &other) {
		animationHandler = other.animationHandler; // deep copy again
		entityId = other.entityId;
		factoryId = other.factoryId;
		name = other.name;
		type = other.type;
		charType = other.charType;
		stats = other.stats;
		abilities = other.abilities; 
		interactions = other.interactions;
		alive = other.alive;
		animationHandler.setEntityName(name);
		render = other.render;
		renderInfo = other.renderInfo;
	}
	return *this;
} 
void entity::update() {
	//if (moving()) {
	//	//if current movement is finished check path and continue, or finish moving
	//	if (animationHandler.getMovement()->isFinished()) {
	//		if (path.turns.size() > 0) {
	//			animationHandler.setMovement(getNextDirection(path), 0, 0, 128, 10);
	//		}
	//		else {
	//			setMoving(false);
	//			setBlockMenus(false);
	//			animationHandler.loadAnimation("idle");
	//			animationHandler.setMovement(movementTypeEnum::idle, 0, 0, 0, animationHandler.getFrameCount()); 
	//		}
	//	}
	//	//if current movement isnt finsihed, continue
	//	else {
	//		animationHandler.step(); 
	//	}
	//}
	//else{
	//	animationHandler.step();  
	//}
	//updateRenderInfo();
}  
abilities& entity::getAbilities() {
	return abilities;
}

const abilities& entity::getAbilities() const {
	return abilities;
}
//GET RID OF THIS!!
void entity::updateRenderInfo() {
	position p = getCombinedPos();
	renderInfo.height = animationHandler.getHeight();
	renderInfo.width = animationHandler.getWidth();
	renderInfo.pos.setX(p.getX());
	renderInfo.pos.setY(p.getY());
	renderInfo.render = render;
	renderInfo.tex = animationHandler.getCurrentTexture();
}
const entityRenderInfo entity::getRenderInfo() {
	updateRenderInfo();
	 return renderInfo; 
} 
void entity::from_Json(const nlohmann::ordered_json& j) {
	if (j.contains("name")) {
		setName(j.at("name").get<std::string>());
	}
	if (j.contains("type")) {
		setType(entityTypeFromString(j.at("type").get<std::string>()));
	}
	if (j.contains("charType")) {
		setCharacterType(stringToCharacterTypeEnum(j.at("charType")));
	}
	if (j.contains("entityId")) {
		setEntityId(j.at("entityId").get<int>());
	}
	if (j.contains("factoryId")) {
		setFactoryId(j.at("factoryId").get<int>());
	}
	if (j.contains("interactions")) {
		interactions = j.at("interactions").get<InteractFlags>();
	}
	if (j.contains("movement")) {
		from_json(j.at("movement"), movement);
	}
	if (j.contains("stats")) {
		//stats = j.at("stats").get<statsContainer>();
		from_json(j.at("stats"), stats);
	}
	//UPDATE THIS to update the abilities state(to load from saves etc) 
	if (j.contains("abilities")) {
		for (const auto& abEntry : j["abilities"]) { 
			std::string abilityName = abEntry.at("name").get<std::string>(); 
			auto abPtr = abilityFactory::getInstance().create(abilityName);
			if (abPtr) {
				abilities.addAbility(std::move(abPtr));
			}
			else {
				logManager::logThis("Failed to create ability: " + abilityName);
			}
		}
	}
	if (j.contains("animationManager")) {
		from_json(j.at("animationManager"), animationHandler);
	}
	if (j.contains("renderInfo")) {
		from_json(j.at("renderInfo"), renderInfo);
	}  
	if (j.contains("alive")) {
		from_json(j.at("alive"), alive);
	}
	 
	nlohmann::ordered_json dumper = to_Json(*this);
	//logManager::logThis("New Entity Dump \n", dumper.dump(4));
}
nlohmann::ordered_json entity::to_Json(const entity& e) {
	ordered_json j;
	//json j;
	j["type"] = entityTypeToString(e.getType());
	j["charType"] = characterTypeEnumToString(e.getCharacterType());
	j["entityId"] = e.getId();
	j["factoryId"] = e.getFactoryId();
	j["name"] = e.getName();
	j["interactions"] = e.getInteractionsConst();
	j["movement"] = e.getMovementConst();
	j["stats"] = e.getStats(); 
	j["alive"] = e.isAlive();
	nlohmann::ordered_json abilitiesArray = nlohmann::ordered_json::array();
	for (const auto& abPtr : e.getAbilities().getAll()) {
		if (abPtr) {
			abilitiesArray.push_back(abPtr->to_Json());  // each subclass implements to_json()
		}
	}
	j["abilities"] = abilitiesArray; 
	j["animationManager"] = e.animationHandler;
	j["renderInfo"] = e.renderInfo; 
	//logManager::logThis("Entity JSON dump:\n" + j.dump(4));
	return j;
}

void entity::spill_guts(std::string s) {
	nlohmann::ordered_json j = to_Json(*this);
	logManager::logThis(s);
	//logManager::logThis("Entity JSON dump:\n" + j.dump(4));
}
void entity::spill_guts() {
	nlohmann::ordered_json j = to_Json(*this);
	//logManager::logThis("Entity JSON dump:\n" + j.dump(4));
}