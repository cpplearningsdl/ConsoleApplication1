#pragma once
#include "json.hpp"
#include <algorithm>

class uses {
private:
	int current;
	int max;
	bool locked;
public:
	uses() : current(0), max(0), locked(0) {}
	uses(int maxUses, int currentUses, bool lock) : current(currentUses), max(maxUses), locked(lock){} 

	uses(const uses&) = default;
	uses& operator=(const uses&) = default;

	int getCurrent() const { return current; }
	int getMax() const { return max; }
	bool getLocked() const { return locked; }

	void setMax(int newMax) {
		max = newMax;
		if (current > max) current = max;
	}

	void setCurrent(int newCurrent) {
		current = newCurrent;
		if (current > max) { current = max; }
	}

	void reset() { current = max; }

	bool canUse() const {
		if (current > 0 && locked == 0) { return true; }
		return false;
	}

	void lock(bool lock) {	locked = lock; }

	void addOne() {
		if (current < max) { current++; }
	}
	void useOne() {
		if (current > 0) {
			--current; 
		} 
	}

	void addUses(int amount) {
		current = std::min(current + amount, max);
	}
	friend void from_json(const nlohmann::json& j, uses& u);
	friend void to_json(nlohmann::json& j, const uses& u);  
};
inline void to_json(nlohmann::json& j, const uses& u) {
	j = nlohmann::json{
		{"current", u.getCurrent()},
		{"max", u.getMax()},
		{"locked", u.getLocked()}
	};
}
 
inline void from_json(const nlohmann::json& j, uses& u) {
	int current = j.value("current", 0);
	int max = j.value("max", 0);
	bool locked = j.value("locked", false);
	u.setMax(max);
	u.setCurrent(current);  
	u.lock(locked);
}