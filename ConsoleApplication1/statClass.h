#pragma once
#include <algorithm>

//current can go above base, for buffs, but for things like HP and overhealing, you can stop that by calling clampCurrentToBase() after you setCurrent() or increaseCurrent()
//you can subtract by increasing with a negative amount.
class statClass {
	private:
		int current;
		int min;
		int base;

	public:
		statClass() : current(0), min(0), base(0) {}
		statClass(int currentVal, int minVal, int baseVal) : current(currentVal), min(minVal), base(baseVal) {
			base = std::max(baseVal, 0);
			min = std::clamp(minVal, 0, baseVal);
			current = std::max(currentVal, 0);
		}

		int getCurrent() const { return current; }
		int getMin() const { return min; }
		int getBase() const { return base; }

		void setCurrent(int newCurrent) { current = std::max(newCurrent, min); }
		void setMin(int newMin) {
			min = std::clamp(newMin, 0, base); 
			if (current < min) { current = min; }
			
		}
		void setBase(int newBase) { 
			base = std::max(newBase, 0);
			if (min < base) { min = base; }
		}

		void increaseCurrent(int amount) { setCurrent(current + amount); }
		void increaseMin(int amount) { setMin(min + amount); }
		void increaseBase(int amount) { setBase(base + amount); }
		void clampCurrentToBase() { if (current > base) current = base; }
};