#include "Dungeon.h"

Dungeon::Dungeon(const std::string& name) : name_(name)
{
}

const std::string& Dungeon::name() const
{
	return name_;
}

void Dungeon::addMonster(std::size_t uniqueIndex)
{
	monsterList_.push_back(uniqueIndex);
}


void Dungeon::clearMonster()
{
	monsterList_.clear();
}

const std::vector<std::size_t>& Dungeon::getMonsterList() const
{
	return monsterList_;
}
