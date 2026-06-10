#pragma once

#include <vector>
#include <memory>

#include "LogSystem.h"
#include "Dungeon.h"
#include "Charactor.h"

#include "RootingTable.h"


class MonsterSpawnSystem {
public:
	struct DI {
		LogSystem& log;
		RootingTable& rootTable;
	};
	MonsterSpawnSystem(DI di);

	std::vector<std::size_t> spawnMonster();
	Charactor* getMonster(std::size_t uniqueIndex);
	void releaseMonster(std::size_t uniqueIndex);

private:
	Charactor* createMonster();
	static int createRandomMonsterSize();

	LogSystem& log_;
	RootingTable& table_;
	std::vector<std::unique_ptr<Charactor>> monsterPool_;
	std::vector<Inventory> monsterInventoryPool_;

};