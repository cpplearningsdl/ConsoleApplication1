#include "animationManager.h"
#include "animationMovementFactory.h"
#include "textureManager.h" 
#include "logManager.h"



animationManager::animationManager()
	:animationName("idle"), frameCount(0), currentIndex(0), heldCount(0), holdFor(0), finished(false), loop(true) {
	setMovement(movementTypeEnum::idle, 0, 0, 0, 1);
}

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
	frameTextures(other.frameTextures),
	height(other.height),
	width(other.width),
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
		frameTextures = other.frameTextures;
		height = other.height;
		width = other.width;
		movement = other.movement ? other.movement->clone() : nullptr;
	}
	return *this;
}

bool animationManager::loadAnimation(const std::string& baseName) {
	animationName = baseName;
	currentIndex = 0;
	const textureDataStruct* data = textureManager::getInstance().getAnimationData(getTextureKey());
	if (!data) {
		logManager::logThis("Error: could not find animation data for " + getTextureKey());
		return false;
	}

	frameCount = data->totalFrames;
	loop = data->loop;  
	heldCount = 0;
	holdFor = 0;
	finished = false;
	chainOverride = "";
	chainAnimationName = data->chainAnimation;
	 

	frameTextures.clear();
	frameTextures.reserve(data->totalFrames);
	//load all frame sizes instead of using pointer to data so we can change size of entities without math every frame
	for (int frame = 0; frame < data->totalFrames; ++frame) {
		std::string key = entityName + "_" + baseName + "_" + std::to_string(frame);

		SDL_Texture* tex = textureManager::getInstance().getFrame(key);
		if (!tex) {
			logManager::logThis("Warning: missing texture for key: " + key);
			return false; 
		}
		frameTextures.push_back(tex);
		height.push_back(data->height);
		width.push_back(data->width);
	}

	logManager::logThis("EntityNamed " + entityName + " Loaded Animation: ", animationName);

	//this system is stupid. need lookups for movement for each animation or something. 
	if (baseName == "idle") {
		setMovement(animationMovementFactory::createMovement(movementTypeEnum::idle, 0, 0, 0, frameCount));
	} 
	return true;
}

void animationManager::setMovement(movementTypeEnum type, float startX, float startY, float distance, int frames, float destinationX, float destinationY) {
	movement = animationMovementFactory::createMovement(type, startX, startY, distance, frames, destinationX, destinationY);
}
 
void animationManager::step() {
	if (finished) return; //might be problematic if movement not finished but animation is?
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
			logManager::logThis("FINISHED"); 
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
	if (j.contains("frameCount")) {
		m.setFrameCount(j.at("frameCount").get<int>());
	}
	if (j.contains("currentIndex")) {
		m.setCurrentIndex(j.at("currentIndex").get<int>());
	}
	if (j.contains("heldCount")) {
		m.setHeldCount(j.at("heldCount").get<int>());
	}
	if (j.contains("holdFor")) {
		m.setHoldFor(j.at("holdFor").get<int>());
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
	m.loadAnimation(m.getAnimationName());
}