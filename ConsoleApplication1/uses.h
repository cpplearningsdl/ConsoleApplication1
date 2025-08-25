#pragma once
#include <algorithm>
class uses {
private:
	int current;
	int max;

public:
	uses() : current(0), max(0) {}

	uses(int maxUses = 0)
		: current(maxUses), max(maxUses) {}

	int getCurrent() const { return current; }
	int getMax() const { return max; }

	void setMax(int newMax) {
		max = newMax;
		if (current > max) current = max;
	}

	void setCurrent(int newCurrent) {
		current = newCurrent;
		if (current > max) { current = max; }
	}

	void reset() { current = max; }

	bool canUse() const { return current > 0; }

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
};
