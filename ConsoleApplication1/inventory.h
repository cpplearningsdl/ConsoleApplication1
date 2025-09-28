#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include "item.h"  

class inventory {
public:
	// Constructors
	inventory(int maxSize = 10);
	inventory(const inventory& other);            // Copy constructor
	inventory& operator=(const inventory& other); // Copy assignment
	inventory(inventory&& other) noexcept = default;            // Move constructor
	inventory& operator=(inventory&& other) noexcept = default; // Move assignment

	// Destructor
	~inventory() = default;

	// Core functions
	bool addItem(std::unique_ptr<item> item);
	bool removeItem(size_t index);
	item* getItem(size_t index) const;

	// Utility
	size_t size() const { return items.size(); }
	int capacity() const { return maxSize; }

private:
	std::vector<std::unique_ptr<item>> items;
	int maxSize;
};
