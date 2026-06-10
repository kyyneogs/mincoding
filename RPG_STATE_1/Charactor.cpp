#include "Charactor.h"

Charactor::Charactor(const std::string& name, std::size_t id, int maxHp, int attack, int defense, int speed, bool playable)
	: name_(name), id_(id), maxHp_(maxHp), hp_(maxHp), attack_(attack), defense_(defense), speed_(speed), playable_(playable) {
}

const std::string& Charactor::name() const
{
	return name_;
}

bool Charactor::isPlayable() const
{
	return playable_;
}

int Charactor::getAttack() const
{
	return attack_;
}

int Charactor::getDefense() const
{
	return defense_;
}

int Charactor::getHp() const
{
	return hp_;
}

int Charactor::getMaxHp() const
{
	return maxHp_;
}

int Charactor::getSpeed() const
{
	return speed_;
}

void Charactor::takeDamage(int damage)
{
	hp_ -= damage;
	hp_ = hp_ > 0 ? hp_ : 0;
}

bool Charactor::isAlive() const
{
	return hp_ > 0;
}
