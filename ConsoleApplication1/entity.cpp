#include "entity.h"
 



entity::entity(int id) {
	entityId = id;

}

void entity::update() {

}

stats& entity::getStats() {
	return stats;
}

const stats& entity::getStats() const {
	return stats;
}

abilities& entity::getAbilities() {
	return abilities;
}

const abilities& entity::getAbilities() const {
	return abilities;
}