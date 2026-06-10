#pragma once

#include <string>
#include "AttributeType.h"

class Charactor {
public:
	Charactor(const std::string& name, std::size_t id, int maxHp, int attack, int defense, int speed, AttributeType type, bool playable);
	~Charactor() = default;

	const std::string& name() const;
	bool isPlayable() const;

	int getAttack() const;
	int getDefense() const;
	int getHp() const;
	int getMaxHp() const;
	int getSpeed() const;
	AttributeType getType() const;

	void takeDamage(int damage);
	bool isAlive() const;

private:
	std::string name_;
	std::size_t id_;
	AttributeType type_;
	bool playable_;
	int maxHp_;
	int hp_; 
	int attack_;
	int defense_;
	int speed_;
};
