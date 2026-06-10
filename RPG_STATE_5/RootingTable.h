#pragma once

#include "Inventory.h"

class RootingTable {
public:
	RootingTable();
	void createGoblinRootInventory(Inventory& inventory);

private:
	struct Root {
		std::string name;
		float probability;
	};

	std::vector<Root> goblinTable_;
};