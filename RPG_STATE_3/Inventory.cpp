#include "Inventory.h"

Inventory::Inventory(std::size_t size)
{
	inv_.reserve(size);
}

std::size_t Inventory::size() const
{
	return inv_.size();
}

std::size_t Inventory::max_size() const
{
	return inv_.capacity();
}

bool Inventory::insertItem(Item item)
{
	bool success{};
	if (inv_.size() < inv_.capacity()) {
		success = true;
		inv_.emplace_back(item);
	}
	return success;
}

void Inventory::removeItem(const std::string name)
{
	for (std::size_t i = 0; i < inv_.size();) {
		if (inv_[i].name == name) {
			inv_.erase(inv_.begin() + i);
		}
		else {
			++i;
		}
	}
}

void Inventory::removeItem(std::size_t index)
{
	if (index < inv_.size()) {
		inv_.erase(inv_.begin() + index);
	}
}

const std::vector<Item>& Inventory::showInventory() const
{
	return inv_;
}

