#include "entity.h"
#include "C:\Users\Keary\source\repos\ConsoleApplication1\ConsoleApplication1\include\json.hpp"
using json = nlohmann::json;

entity::entity(int id) {
	factoryId = id; 
}	

void entity::update() {

}
 
abilities& entity::getAbilities() {
	return abilities;
}

const abilities& entity::getAbilities() const {
	return abilities;
}

json entity::entityToJson(const entity& e) {
	json j;
	j["entityId"] = e.getId();
	j["factoryId"] = e.getFactoryId();
	j["name"] = e.getName();
	j["stats"] = e.getStats();
	return j;
}