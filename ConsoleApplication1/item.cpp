#include "item.h"
#include <utility>

// Default ctor
item::item() : name("Unknown"), value(0) {}

// Custom ctor
item::item(const std::string& n, int v) : name(n), value(v) {}

// Dtor
item::~item() = default;

// Copy ctor
item::item(const item& other) : name(other.name), value(other.value) {}

// Move ctor
item::item(item&& other) noexcept
	: name(std::move(other.name)), value(other.value) {
	other.value = 0; // optional cleanup
}

// Copy assignment
item& item::operator=(const item& other) {
	if (this != &other) {
		name = other.name;
		value = other.value;
	}
	return *this;
}

// Move assignment
item& item::operator=(item&& other) noexcept {
	if (this != &other) {
		name = std::move(other.name);
		value = other.value;
		other.value = 0;
	}
	return *this;
}

// Clone for polymorphic copying
std::unique_ptr<item> item::clone() const {
	return std::make_unique<item>(*this);
}
