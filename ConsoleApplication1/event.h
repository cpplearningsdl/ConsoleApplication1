#pragma once  
#include <variant>
#include <string>
#include <cstdint>

class entity;

// Base event struct (mainly for conceptual clarity)
struct baseEvent {
	virtual ~baseEvent() = default;
};



