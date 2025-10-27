#include "turnManager.h"
#include "overLoaded.h" 

turnManager::turnManager() {
};

void turnManager::newTurn() {

}


void turnManager::handleEvent(const gameEvent& event) {
	std::visit(overloaded{
   [&](const newTurnEvent& e) {
 
	}, 
	 [&](const startTurnEvent& e) {

	},
[](auto&) {}
		}, event);

}