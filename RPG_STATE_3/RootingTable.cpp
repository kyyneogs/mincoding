#include "RootingTable.h"

#include <random>

RootingTable::RootingTable()
{
	goblinTable_.reserve(5);
	goblinTable_.push_back({ "종결 레전드 아이템", 0.1 });
	goblinTable_.push_back({ "전설 아이템", 0.2 });
	goblinTable_.push_back({ "유니크", 0.3 });
	goblinTable_.push_back({ "잡템1", 0.75 });
	goblinTable_.push_back({ "치료잡템1", 0.75 });
}

void RootingTable::createGoblinRootInventory(Inventory& inventory)
{
	static std::mt19937 rng{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	for (std::size_t i = 0; i < goblinTable_.size(); ++i) {
		if (dist(rng) < goblinTable_[i].probability) {
			if (inventory.size() < inventory.max_size()) {
				inventory.insertItem({ goblinTable_[i].name });
			}
		}
	}
}
