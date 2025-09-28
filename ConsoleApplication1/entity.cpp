
#include "entity.h"
#include "json.hpp"
//using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

entity::entity() {

}
entity::entity(const entity& other)
	: animationHandler(other.animationHandler) // uses deep copy from animationManager
{
	entityId = other.entityId;
	factoryId = other.factoryId;
	name = other.name;
	stats = other.stats;
	abilities = other.abilities; 
	pos = other.pos;
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
		stats = other.stats;
		abilities = other.abilities;
		pos = other.pos; 
		animationHandler.setEntityName(name);
		render = other.render;
		renderInfo = other.renderInfo;
	}
	return *this;
}
//void entity::update() {
//	animationHandler.step();
//	renderInfo.textureKey = animationHandler.getTextureKey(); 
//}
// 
//NEED TO ADD MOVEMENT OFFSET TO  POSITION!!!!!
void entity::update() {
	animationHandler.step(); 
	updateEntityRenderInfo(renderInfo, animationHandler.getCurrentTexture(), getCombinedPos(), animationHandler.getHeight(), animationHandler.getWidth(), getRender());
	//updateEntityRenderInfo(renderInfo,animationHandler.frameTextures)
} 
void entity::updateRenderInfo() {
	updateEntityRenderInfo(renderInfo, animationHandler.getCurrentTexture(), getCombinedPos(), animationHandler.getHeight(), animationHandler.getWidth(), getRender());
}
abilities& entity::getAbilities() {
	return abilities;
}

const abilities& entity::getAbilities() const {
	return abilities;
}

const entityRenderInfo& entity::getRenderInfo() const {
	 return renderInfo; 
} 
void entity::from_Json(const nlohmann::ordered_json& j) {
	if (j.contains("name")) {
		setName(j.at("name").get<std::string>());
	}
	if (j.contains("entityId")) {
		setEntityId(j.at("entityId").get<int>());
	}
	if (j.contains("factoryId")) {
		setFactoryId(j.at("factoryId").get<int>());
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
	if (j.contains("position")) { 
		from_json(j.at("position"), pos);
	}
	 
	nlohmann::ordered_json dumper = to_Json(*this);
	//logManager::logThis("New Entity Dump \n", dumper.dump(4));
}
nlohmann::ordered_json entity::to_Json(const entity& e) {
	ordered_json j;
	//json j;
	j["entityId"] = e.getId();
	j["factoryId"] = e.getFactoryId();
	j["name"] = e.getName();
	j["stats"] = e.getStats();
	j["position"] = e.getPos();
	nlohmann::ordered_json abilitiesArray = nlohmann::ordered_json::array();
	for (const auto& abPtr : e.getAbilities().getAll()) {
		if (abPtr) {
			abilitiesArray.push_back(abPtr->to_Json());  // each subclass implements to_json()
		}
	}
	j["abilities"] = abilitiesArray; 
	j["animationManager"] = e.animationHandler;
	j["renderInfo"] = e.renderInfo; 
	logManager::logThis("Entity JSON dump:\n" + j.dump(4));
	return j;
}

void entity::spill_guts() {
	nlohmann::ordered_json j = to_Json(*this);
	logManager::logThis("Entity JSON dump:\n" + j.dump(4));
}