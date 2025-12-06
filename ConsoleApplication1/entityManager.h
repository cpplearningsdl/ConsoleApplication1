#pragma once
#include <vector>
#include "entity.h"
#include "entityFactory.h"
#include "entityTypeEnum.h"
#include "event.h"
#include "view.h"

struct turnContext;
struct startDialogueEvent; 

class entityManager {
	public: 
		entityManager();
		~entityManager();
		  
		void addEntityFromJson(const std::string& jsonFilePath, const viewPort& v);
		entity* createEntity(int id, ENTITYTYPEENUM type, const viewPort& v);
		void addTileToFloorMap(entity* e, const viewPort& v);
		void removeEntityFromGame(int id, viewPort& v);

		entity&  getEntityById(int id);
		std::vector<std::unique_ptr<entity>>& getEntities() { return entities; }
		std::vector<std::unique_ptr<entity>>& getTiles() { return tiles; }
		std::vector<entity*>& getFloorMap() { return floorMap; }
		void resizeFloorMap(int s) { floorMap.resize(s); }


		 
		void processStartDialogueEvent(turnContext& ctx, startDialogueEvent& e, eventPhase phase);
	private:
		std::vector<std::unique_ptr<entity>> entities;
		std::vector<std::unique_ptr<entity>> tiles;
		std::vector<entity*> floorMap;
		int nextId;
};
