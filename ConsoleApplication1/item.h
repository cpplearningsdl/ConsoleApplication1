#pragma once
#include <string>
#include <memory>

class item {
public:
	item();                                        // default ctor
	item(const std::string& name, int value);      // custom ctor

	~item();                                       // dtor

	item(const item& other);                       // copy ctor
	item(item&& other) noexcept;                   // move ctor

	item& operator=(const item& other);            // copy assignment
	item& operator=(item&& other) noexcept;        // move assignment

	virtual std::unique_ptr<item> clone() const;   // for polymorphic copying

	std::string getName() const { return name; }
	int getValue() const { return value; }

protected:
	std::string name;
	int value;
};
