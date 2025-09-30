#pragma once 
#include <vector>
#include <string>
#include "textureManager.h" 
#include "animationMovement.h"
#include "movementTypeEnum.h"
#include "position.h"
#include "json.hpp"
#include <SDL3/SDL.h>

class animationManager {
public:
	animationManager();
	~animationManager() = default;

	// Deep copy constructor
	animationManager(const animationManager& other); 
	// Deep copy assignment
	animationManager& operator=(const animationManager& other);

	// Move semantics
	animationManager(animationManager&&) noexcept = default;
	animationManager& operator=(animationManager&&) noexcept = default;
	 
	const animationMovement* getMovement() const { return movement.get(); }

	bool loadAnimation(const std::string& baseName);
	 
	void step(); 
	void reset();
	 
	void setMovement(movementTypeEnum type, float startX, float startY, float distance, int frames);
	void setMovement(std::unique_ptr<animationMovement> mvt) {	movement = std::move(mvt);	} 

	// Override the chain animation (die after damage instead of go back to idle, for example)
	void setChainOverride(const std::string& nextAnim); 
	// Clear any chain override (back to using frame.chainAnimation)
	void clearChainOverride(); 
	// Immediately restart with the chain animation (override if set)
	void restartChain();
	   
	const std::string& getAnimationName() const;
	const std::string getTextureKey() const;
	const std::string& getEntityName() const { return entityName; } 
	const size_t getCurrentIndex() const { return currentIndex; }
	const int getHeldCount() const { return heldCount;	}
	const int getFrameCount() const { return frameCount; }
	const int getHoldFor() const { return holdFor; }
	const bool getFinished() const { return finished; }
	const bool getLoop() const { return loop; }
	bool isFinished() const; 
	const std::string& getChainAnimationName() const { return chainAnimationName; }
	const std::string& getChainOverride() const { return chainOverride; }

	void setEntityName(std::string n) { entityName = n; }
	void setAnimationName(std::string n) { animationName = n; } 
	void setChainAnimationName(std::string n) { chainAnimationName = n; } 
	void setFrameCount(int t) { frameCount = t; }
	void setCurrentIndex(size_t i) { currentIndex = i; }
	void setHeldCount(int c) { heldCount = c; }
	void setHoldFor(int c) { holdFor = c; }
	void setLoop(bool l) { loop = l; }
	void setFinished(bool f) { finished = f; } 
	const position getPos() { return position(movement->getX(), movement->getY()); }
	SDL_Texture* getCurrentTexture() { return frameTextures[getCurrentIndex()]; }
	const int getHeight() const { return height[getCurrentIndex()]; }
	const int getWidth() const { return width[getCurrentIndex()]; }

	friend void to_json(nlohmann::ordered_json& j, const animationManager& m);
	friend void from_json(const nlohmann::ordered_json& j, animationManager& m);
private: 
	std::vector<SDL_Texture*> frameTextures;
	std::vector<int> height;
	std::vector<int> width;

	std::string animationName;
	std::string entityName;
	size_t currentIndex;
	int frameCount;
	int heldCount;
	int holdFor;
	bool loop;
	bool finished; 
	std::string chainAnimationName;
	std::string chainOverride; 
	std::unique_ptr<animationMovement> movement;
};

void to_json(nlohmann::ordered_json& j, const animationManager& m);
void from_json( const nlohmann::ordered_json& j, animationManager& m);