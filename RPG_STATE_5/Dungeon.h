#pragma once

#include "Charactor.h"

#include <vector>
#include <string>

class Dungeon {
public:
	Dungeon(const std::string& name);
	~Dungeon() = default;

	const std::string& name() const;
	void addMonster(std::size_t uniqueIndex);
	void clearMonster();

	const std::vector<std::size_t>& getMonsterList() const;
private:
	const std::string name_;
	std::vector<std::size_t> monsterList_;
};
