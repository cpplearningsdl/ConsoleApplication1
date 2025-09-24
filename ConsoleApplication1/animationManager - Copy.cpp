#include "animationManager.h"
#include "animationMovementFactory.h"
#include "textureManager.h" 
#include "logManager.h"



animationManager::animationManager()
	:animationName("idle"), frameCount(0), currentIndex(0), heldCount(0), holdFor(0), finished(false), loop(true) {}

animationManager::animationManager(const animationManager& other)
	: entityName(other.entityName),
	animationName(other.animationName), 
	frameCount(other.frameCount),
	currentIndex(other.currentIndex),
	heldCount(other.heldCount),
	holdFor(other.holdFor),
	finished(other.finished),
	loop(other.loop),
	chainOverride(other.chainOverride),
	chainAnimationName(other.chainAnimationName),
	movement(other.movement ? other.movement->clone() : nullptr) // deep clone
{}

animationManager& animationManager::operator=(const animationManager& other) {
	if (this != &other) { 
		entityName = other.entityName;
		animationName = other.animationName; 
		frameCount = other.frameCount;
		currentIndex = other.currentIndex;
		heldCount = other.heldCount;
		holdFor = other.holdFor;
		finished = other.finished;
		loop = other.loop;
		chainOverride = other.chainOverride;
		chainAnimationName = other.chainAnimationName;
		movement = other.movement ? other.movement->clone() : nullptr;
	}
	return *this;
}

bool animationManager::loadAnimation(const std::string& baseName) {
	const textureDataStruct* data = textureManager::getInstance().getAnimationData(getTextureKey());
	logManager::logThis("KEY? ", getTextureKey());
	frameCount = data->totalFrames;
	loop = data->loop; 
	currentIndex = 0;
	heldCount = 0;
	holdFor = 0;
	finished = false;
	chainOverride = "";
	chainAnimationName = data->chainAnimation;
	animationName = baseName; 

	logManager::logThis("EntityNamed " + entityName + " Loaded Animation: ", animationName);
	return true;

	//probably should attach the correct animationMovement here(even idle/no movement) or the place that loads the animation should et it(even more probably)?
}

void animationManager::setMovement(movementTypeEnum type, float startX, float startY, float distance, int frames) {
	movement = animationMovementFactory::createMovement(type, startX, startY, distance, frames);
}
 
void animationManager::step() {
	if (finished) return; 
	// Hold frame for N steps
	if (heldCount < holdFor) {
		heldCount++;
		return;
	} 
	// Reset hold counter and advance frame
	heldCount = 0;
	currentIndex++;

	//advance animation movement
	if (movement && !movement->isFinished()) {
		movement->step();
	}

	if (currentIndex >= getFrameCount()) {
		if (getLoop()) {
			currentIndex = 0;
		}
		else {
			finished = true;

			// Use override if present, otherwise use frame.chainAnimation
			std::string nextAnim = chainOverride.empty()
				? getChainAnimationName()
				: getChainOverride();

			// clear override after use
			chainOverride.clear();

			if (!nextAnim.empty()) {
				loadAnimation(nextAnim);
			}
			else {
				// Freeze on last frame
				currentIndex = getFrameCount() - 1;
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
	if (getCurrentIndex() > getFrameCount()) return; 
	// Use override if present, otherwise use frame.chainAnimation
	std::string nextAnim = chainOverride.empty()
		? getChainAnimationName()
		: getChainOverride();

	// clear override after use
	chainOverride.clear();

	if (!nextAnim.empty()) {
		loadAnimation(nextAnim);
	}
	else {
		// No chain specified, freeze at last frame
		currentIndex = getFrameCount() - 1;
		finished = true;
	}
}

  
bool animationManager::isFinished() const {
	return finished;
}

const std::string& animationManager::getAnimationName() const {
	return animationName;
}
const std::string animationManager::getTextureKey() const { 
	//std::string texkey = getEntityName() + "_" + getAnimationName() + "_" + std::to_string(getCurrentIndex());
	//logManager::logThis("texkey ", texkey);
	return getEntityName() + "_" + getAnimationName() + "_" + std::to_string(getCurrentIndex());
}
void to_json(nlohmann::ordered_json& j, const animationManager& m) {
	j = nlohmann::ordered_json{
		{"entityName", m.getEntityName() },
		{"animationName", m.getAnimationName()},
		{"chainAnimationName", m.getChainAnimationName()},
		{"frameCount", m.getFrameCount() },
		{"currentIndex", m.getCurrentIndex()},
		{"heldCount", m.getHeldCount()},
		{"holdFor", m.getHoldFor()},
		{"finished", m.getFinished()},
		{"loop", m.getLoop()},
		{"chainOverride", m.getChainOverride()}
	};

	if (m.getMovement()) {
		nlohmann::ordered_json moveJson;
		m.getMovement()->to_json(moveJson);
		j["animationMovement"] = std::move(moveJson);
	}
}

void from_json(const nlohmann::ordered_json& j,animationManager& m) { 
	if (j.contains("entityName")) {
		m.setEntityName(j.at("entityName").get<std::string>());
	}
	if (j.contains("animationName")) {
		m.setAnimationName(j.at("animationName").get<std::string>());
	}
	if (j.contains("chainAnimationName")) {
		m.setChainAnimationName(j.at("chainAnimationName").get<std::string>());
	}
	if (j.contains("size")) {
		m.setFrameCount(j.at("size").get<int>());
	}
	if (j.contains("currentIndex")) {
		m.setCurrentIndex(j.at("currentIndex").get<int>());
	}
	if (j.contains("heldCount")) {
		m.setHeldCount(j.at("heldCount").get<int>());
	}
	if (j.contains("holdFor")) {
		m.setHoldFor(j.at("holdCount").get<int>());
	}
	if (j.contains("finished")) {
		m.setFinished(j.at("finished").get<bool>());
	}
	if (j.contains("loop")) {
		m.setLoop(j.at("loop").get<bool>());
	}
	if (j.contains("chainOverride")) {
		m.setChainOverride(j.at("chainOverride").get<std::string>());
	}
	if (j.contains("animationMovement")) {
		const auto& jm = j.at("animationMovement");

		// Factory creates the correct subclass and loads JSON internally
		auto movePtr = animationMovementFactory::createFromJson(jm);

		if (movePtr) {
			m.setMovement(std::move(movePtr));
		}
	}
}