#include "animationManager.h"
#include "textureManager.h" 
#include "logManager.h"

animationManager::animationManager()
	: currentIndex(0), heldCount(0), holdFor(0), finished(false) {}

bool animationManager::loadAnimation(const std::string& baseName) {
	frames.clear();
	currentIndex = 0;
	heldCount = 0;
	holdFor = 0;
	finished = false;
	chainOverride.clear();
	name = baseName;
	 
	std::string firstKey = baseName + "_0";
	const textureDataStruct* base = textureManager::getInstance().getAnimationData(firstKey);
	if (!base) {
		logManager::logThis("No animationData for key ", firstKey);
		return false;
	}

	int total = base->totalFrames;
	if (total <= 0) total = 1; 

	// Load frames _0 ... _(total-1)
	for (int i = 0; i < total; ++i) {
		std::string key = baseName + "_" + std::to_string(i);
		const textureDataStruct* data = textureManager::getInstance().getAnimationData(key);
		if (!data) {
			logManager::logThis("Missing Frame: ", key); 
			continue;
		}
		frames.push_back(*data); 
	} 
	return !frames.empty();
}

void animationManager::step() {
	if (frames.empty() || finished) return;

	const textureDataStruct& frame = frames[currentIndex];

	// Hold frame for N steps
	if (heldCount < holdFor) {
		heldCount++;
		return;
	}

	// Reset hold counter and advance frame
	heldCount = 0;
	currentIndex++;

	if (currentIndex >= frames.size()) {
		if (frames.back().loop) {
			currentIndex = 0;
		}
		else {
			finished = true;

			// Use override if present, otherwise use frame.chainAnimation
			std::string nextAnim = chainOverride.empty()
				? frames.back().chainAnimation
				: chainOverride;

			// clear override after use
			chainOverride.clear();

			if (!nextAnim.empty()) {
				loadAnimation(nextAnim);
			}
			else {
				// Freeze on last frame
				currentIndex = frames.size() - 1;
			}
		}
	}
}

void animationManager::reset() {
	currentIndex = 0;
	heldCount = 0;
	holdFor = 0;
	finished = false;
}

void animationManager::setChainOverride(const std::string& nextAnim) {
	chainOverride = nextAnim;
}

void animationManager::clearChainOverride() {
	chainOverride.clear();
}

void animationManager::restartChain() {
	if (frames.empty()) return;

	// Use override if present, otherwise use frame.chainAnimation
	std::string nextAnim = chainOverride.empty()
		? frames.back().chainAnimation
		: chainOverride;

	// clear override after use
	chainOverride.clear();

	if (!nextAnim.empty()) {
		loadAnimation(nextAnim);
	}
	else {
		// No chain specified, freeze at last frame
		currentIndex = frames.size() - 1;
		finished = true;
	}
}

const textureDataStruct* animationManager::getCurrentFrame() const {
	if (frames.empty()) return nullptr;
	return &frames[currentIndex];
}

bool animationManager::isFinished() const {
	return finished;
}

const std::string& animationManager::getName() const {
	return name;
}
