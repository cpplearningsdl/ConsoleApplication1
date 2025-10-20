#pragma once
#include <cstdint>
#include "json.hpp"
#include "logManager.h"
using json = nlohmann::ordered_json;

enum class InteractFlags : uint32_t {
	None = 0,
	Hover = 1 << 0,
	Click = 1 << 1,
	Attack = 1 << 2,
	Ability = 1 << 3,
	Talk = 1 << 4,
	Shop = 1 << 5
};

// --- bitwise ops ---
inline InteractFlags operator|(InteractFlags a, InteractFlags b) {
	return static_cast<InteractFlags>(
		static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}
inline InteractFlags operator&(InteractFlags a, InteractFlags b) {
	return static_cast<InteractFlags>(
		static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}
inline InteractFlags operator~(InteractFlags a) {
	return static_cast<InteractFlags>(~static_cast<uint32_t>(a));
}

// --- set and test ---
inline void setInteraction(InteractFlags& flags, InteractFlags flag, bool value) {
	if (value)
		flags = flags | flag;   // set bit to 1
	else
		flags = flags & ~flag;  // set bit to 0
}

inline bool canInteract(InteractFlags flags, InteractFlags flag) {
	return static_cast<bool>(flags & flag); // true if bit is 1
}

inline void to_json(json& j, const InteractFlags& flags) {
	j = json::object();
	j["hover"] = canInteract(flags, InteractFlags::Hover);
	j["click"] = canInteract(flags, InteractFlags::Click);
	j["attack"] = canInteract(flags, InteractFlags::Attack);
	j["ability"] = canInteract(flags, InteractFlags::Ability);
	j["talk"] = canInteract(flags, InteractFlags::Talk);
	j["shop"] = canInteract(flags, InteractFlags::Shop);
}

inline void from_json(const json& j, InteractFlags& flags) {
	flags = InteractFlags::None;
	setInteraction(flags, InteractFlags::Hover, j.value("hover", false));
	setInteraction(flags, InteractFlags::Click, j.value("click", false));
	setInteraction(flags, InteractFlags::Attack, j.value("attack", false));
	setInteraction(flags, InteractFlags::Ability, j.value("ability", false));
	setInteraction(flags, InteractFlags::Talk, j.value("talk", false));
	setInteraction(flags, InteractFlags::Shop, j.value("shop", false));
}
