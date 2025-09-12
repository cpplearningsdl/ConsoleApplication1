#pragma once 
#include <vector>
#include <string>
#include "textureManager.h" 
#include "animationMovement.h"
#include "movementDirectionEnum.h"

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

	 
	bool loadAnimation(const std::string& baseName);
	 
	void step(); 
	void reset();
	 
	void setMovement(movementDirectionEnum type, float startX, float startY, float distance, int frames);
	// Override the chain animation (die after damage instead of go back to idle, for example)
	void setChainOverride(const std::string& nextAnim); 
	// Clear any chain override (back to using frame.chainAnimation)
	void clearChainOverride(); 
	// Immediately restart with the chain animation (override if set)
	void restartChain();
	 
	const textureDataStruct* getCurrentFrame() const; 
	const std::vector<textureDataStruct>& getFrames() const { return frames; }
	const std::string& getName() const;
	const size_t getCurrentIndex() const { return currentIndex; }
	const int getHeldCount() const { return heldCount;	}
	const int getHoldFor() const { return holdFor; }
	const bool getFinished() const { return finished; }
	bool isFinished() const; 
	const std::string getChainOverride() const { return chainOverride; }

	void setName(std::string n) { name = n; }
	void setCurrentIndex(size_t i) { currentIndex = i; }
	void setHeldCount(int c) { heldCount = c; }
	void setHoldFor(int c) { holdFor = c; }
	void setFinished(bool f) { finished = f; }

	friend void to_json(nlohmann::ordered_json& j, const animationManager& m);
private:
	std::vector<textureDataStruct> frames;
	std::string name;
	size_t currentIndex;
	int heldCount;
	int holdFor;
	bool finished;
	std::string chainOverride; 
	std::unique_ptr<animationMovement> movement;
};

void to_json(nlohmann::ordered_json& j, const animationManager& m);