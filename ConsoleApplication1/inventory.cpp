#include "inventory.h"

inventory::inventory(int maxSize) : maxSize(maxSize) {
	if (maxSize <= 0) {
		throw std::invalid_argument("inventory size must be positive");
	}
}

// Deep copy constructor
inventory::inventory(const inventory& other) : maxSize(other.maxSize) {
	items.reserve(other.items.size());
	for (const auto& item : other.items) {
		if (item) {
			items.push_back(item->clone()); // relies on Item::clone()
		}
	}
}

// Deep copy assignment
inventory& inventory::operator=(const inventory& other) {
	if (this == &other) return *this;

	maxSize = other.maxSize;
	items.clear();
	items.reserve(other.items.size());
	for (const auto& item : other.items) {
		if (item) {
			items.push_back(item->clone());
		}
	}
	return *this;
}

bool inventory::addItem(std::unique_ptr<item> item) {
	if (items.size() >= static_cast<size_t>(maxSize)) {
		return false; // full
	}
	items.push_back(std::move(item));
	return true;
}

bool inventory::removeItem(size_t index) {
	if (index >= items.size()) {
		return false;
	}
	items.erase(items.begin() + index);
	return true;
}

item* inventory::getItem(size_t index) const {
	if (index >= items.size()) {
		return nullptr;
	}
	return items[index].get();
}
