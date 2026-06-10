#include "MonsterSpawnSystem.h"

#include <random>

MonsterSpawnSystem::MonsterSpawnSystem(DI di) : log_(di.log), table_(di.rootTable)
{
	monsterPool_.resize(100);
	monsterInventoryPool_.reserve(100);
	for (std::size_t i = 0; i < monsterInventoryPool_.capacity(); ++i) {
		monsterInventoryPool_.emplace_back(10);
	}
}

std::vector<std::size_t> MonsterSpawnSystem::spawnMonster()
{
	std::vector<std::size_t> result;
	std::size_t monsterSpawnCount = createRandomMonsterSize();
	for (std::size_t i = 0; i < monsterSpawnCount; ++i) {
		auto* monster = createMonster();
		if (!monster) {
			break;
		}

		result.push_back(monster->index());
	}

	return result;
}

Charactor* MonsterSpawnSystem::getMonster(std::size_t uniqueIndex)
{
	return monsterPool_[uniqueIndex].get();
}

void MonsterSpawnSystem::releaseMonster(std::size_t uniqueIndex)
{
	if (monsterPool_[uniqueIndex]) {
		monsterPool_[uniqueIndex].reset();
		monsterInventoryPool_[uniqueIndex].clear();
	}
}

Charactor* MonsterSpawnSystem::createMonster()
{
	Charactor* pMonster{};

	for (std::size_t i = 0; i < monsterPool_.size(); ++i) {
		if (!monsterPool_[i]) {
			auto& inventory = monsterInventoryPool_[i];
			table_.createGoblinRootInventory(inventory);
			monsterPool_[i] = std::make_unique<Charactor>(i, "Goblin", i, 60, 4, 2, 3, 80, 1, AttributeType::Ground, inventory, false);
			pMonster = monsterPool_[i].get();

			Weapon monsterWeapon = { "고블린 단검", 2 };
			Sheild monsterSheild = { "고블린 방패", 1 };
			pMonster->equipWeapon(monsterWeapon);
			pMonster->equipSheild(monsterSheild);
			break;
		}
	}

	return pMonster;
}

int MonsterSpawnSystem::createRandomMonsterSize()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dist(1, 5);
	return dist(gen);
}
