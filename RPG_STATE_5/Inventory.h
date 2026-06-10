#pragma once

#include <vector>
#include "Item.hpp"

class Inventory {
public:
	Inventory(std::size_t size);
	~Inventory() = default;

	std::size_t size() const;
	std::size_t max_size() const;

	bool insertItem(Item item);
	void removeItem(const std::string name);
	void removeItem(std::size_t index);
	void clear();

	const std::vector<Item>& showInventory() const;
private:
	std::vector<Item> inv_;
};