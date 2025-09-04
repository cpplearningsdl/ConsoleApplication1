#pragma once
#include <algorithm>
#include "C:\Users\Keary\source\repos\ConsoleApplication1\ConsoleApplication1\include\json.hpp"

//current can go above base, for buffs, but for things like HP and overhealing, you can stop that by calling lockCurrentToBase() after you setCurrent() or increaseCurrent()
//you can subtract by increasing with a negative amount.
class statClass {
	private:
		int current;
		int min;
		int base;
		bool clamped;

	public:
		statClass() : current(0), min(0), base(0), clamped(false) {}
		statClass(int currentVal, int minVal, int baseVal, bool setClamped = false) : current(currentVal), min(minVal), base(baseVal), clamped(setClamped) {
			base = std::max(baseVal, 0);
			min = std::clamp(minVal, 0, baseVal);
			current = std::max(currentVal, min);
		}

		int getCurrent() const { return current; }
		int getMin() const { return min; }
		int getBase() const { return base; }
		bool isClamped() const { return clamped; }

		void setCurrent(int newCurrent) { 
			current = std::max(newCurrent, min);
			if (clamped == true && current > base) { current = base; }
		}
		void setMin(int newMin) {
			min = std::clamp(newMin, 0, base); 
			if (current < min) { current = min; } 
		}
		void setBase(int newBase) { 
			base = std::max(newBase, 0);
			if (min > base) { min = base; }
			if (clamped && current > base) { current = base; }
		}

		void increaseCurrent(int amount) { setCurrent(current + amount); }
		void increaseMin(int amount) { setMin(min + amount); }
		void increaseBase(int amount) { setBase(base + amount); }
		void clampCurrentToBaseThisTime() { if (current > base) current = base; }
		void setClamped(bool b) { clamped = b; }

};

//to json
inline void to_json(nlohmann::json& j, const statClass& s) {
	j = nlohmann::json{
		{"current", s.getCurrent()},
		{"min",     s.getMin()},
		{"base",    s.getBase()},
		{"clamped", s.isClamped()}
	};
}

inline void from_json(const nlohmann::json& j, statClass& s) {
	s.setCurrent(j.value("current", 0));
	s.setMin(j.value("min", 0));
	s.setBase(j.value("base", 0));
	s.setClamped(j.value("clamped", false));
}