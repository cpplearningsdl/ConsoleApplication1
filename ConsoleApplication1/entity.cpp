#include "entity.h"
  
entity::entity(int id) {
	entityId = id;

}

void entity::update() {

}

 

abilities& entity::getAbilities() {
	return abilities;
}

const abilities& entity::getAbilities() const {
	return abilities;
}