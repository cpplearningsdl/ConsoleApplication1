#pragma once 
#include <vector>
#include <string>
#include "textureManager.h" 

class animationManager {
public:
	animationManager();
	 
	bool loadAnimation(const std::string& baseName);
	 
	void step(); 
	void reset();

	// Override the chain animation (die after damage instead of go back to idle, for example)
	void setChainOverride(const std::string& nextAnim);

	// Clear any chain override (back to using frame.chainAnimation)
	void clearChainOverride();

	// Immediately restart with the chain animation (override if set)
	void restartChain();
	 
	const textureDataStruct* getCurrentFrame() const; 
	bool isFinished() const; 
	const std::string& getName() const;

private:
	std::vector<textureDataStruct> frames;
	std::string name;
	size_t currentIndex;
	int heldCount;
	int holdFor;
	bool finished;
	std::string chainOverride; 
};
