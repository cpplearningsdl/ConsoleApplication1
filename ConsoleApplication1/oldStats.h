#pragma once
#include <algorithm> // for std::clamp

class stats {
public:
	struct statBlock {
		int level;
		int experience;
		int experienceNeeded;

		int hp;
		int maxHp;

		int def;
		int maxDef;

		int attack;
		int maxAttack;

		int intelligence;
		int maxIntelligence;

		int mind;
		int maxMind;

		int growth;
	};

private:
	statBlock base;
	statBlock current;

public:
	stats()
		: base{}, current{} {}

	stats(const statBlock& baseStats)
		: base(baseStats), current(baseStats) {}

	// ===== getters for full structs =====
	const statBlock& getBase() const { return base; }
	const statBlock& getCurrent() const { return current; }

	// ===== base getters =====
	int getBaseLevel() const { return base.level; }
	int getBaseExperience() const { return base.experience; }
	int getBaseExperienceNeeded() const { return base.experienceNeeded; }
	int getBaseHp() const { return base.hp; }
	int getBaseMaxHp() const { return base.maxHp; }
	int getBaseDef() const { return base.def; }
	int getBaseMaxDef() const { return base.maxDef; }
	int getBaseAttack() const { return base.attack; }
	int getBaseMaxAttack() const { return base.maxAttack; }
	int getBaseIntelligence() const { return base.intelligence; }
	int getBaseMaxIntelligence() const { return base.maxIntelligence; }
	int getBaseMind() const { return base.mind; }
	int getBaseMaxMind() const { return base.maxMind; }
	int getBaseGrowth() const { return base.growth; }

	// ===== current getters =====
	int getCurrentLevel() const { return current.level; }
	int getCurrentExperience() const { return current.experience; }
	int getCurrentExperienceNeeded() const { return current.experienceNeeded; }
	int getCurrentHp() const { return current.hp; }
	int getCurrentMaxHp() const { return current.maxHp; }
	int getCurrentDef() const { return current.def; }
	int getCurrentMaxDef() const { return current.maxDef; }
	int getCurrentAttack() const { return current.attack; }
	int getCurrentMaxAttack() const { return current.maxAttack; }
	int getCurrentIntelligence() const { return current.intelligence; }
	int getCurrentMaxIntelligence() const { return current.maxIntelligence; }
	int getCurrentMind() const { return current.mind; }
	int getCurrentMaxMind() const { return current.maxMind; }
	int getCurrentGrowth() const { return current.growth; }

	// ===== base setters =====
	void setBaseLevel(int v) { base.level = v; }
	void setBaseExperience(int v) { base.experience = v; }
	void setBaseExperienceNeeded(int v) { base.experienceNeeded = v; }
	void setBaseHp(int v) { base.hp = v; }
	void setBaseMaxHp(int v) { base.maxHp = v; }
	void setBaseDef(int v) { base.def = v; }
	void setBaseMaxDef(int v) { base.maxDef = v; }
	void setBaseAttack(int v) { base.attack = v; }
	void setBaseMaxAttack(int v) { base.maxAttack = v; }
	void setBaseIntelligence(int v) { base.intelligence = v; }
	void setBaseMaxIntelligence(int v) { base.maxIntelligence = v; }
	void setBaseMind(int v) { base.mind = v; }
	void setBaseMaxMind(int v) { base.maxMind = v; }
	void setBaseGrowth(int v) { base.growth = v; }

	// ===== current setters (with clamping) =====
	void setCurrentLevel(int v) { current.level = v; }
	void setCurrentExperience(int v) { current.experience = v; }
	void setCurrentExperienceNeeded(int v) { current.experienceNeeded = v; }
	void setCurrentHp(int v) { current.hp = std::clamp(v, 0, current.maxHp); }
	void setCurrentMaxHp(int v) { current.maxHp = v; }
	void setCurrentDef(int v) { current.def = std::clamp(v, 0, current.maxDef); }
	void setCurrentMaxDef(int v) { current.maxDef = v; }
	void setCurrentAttack(int v) { current.attack = std::clamp(v, 0, current.maxAttack); }
	void setCurrentMaxAttack(int v) { current.maxAttack = v; }
	void setCurrentIntelligence(int v) { current.intelligence = std::clamp(v, 0, current.maxIntelligence); }
	void setCurrentMaxIntelligence(int v) { current.maxIntelligence = v; }
	void setCurrentMind(int v) { current.mind = std::clamp(v, 0, current.maxMind); }
	void setCurrentMaxMind(int v) { current.maxMind = v; }
	void setCurrentGrowth(int v) { current.growth = v; }
};
