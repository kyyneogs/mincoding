#include "BattleSystem.h"

#include "LogSystem.h"
#include "Charactor.h"

#include <sstream>

namespace {
	void makeBattleLog(std::stringstream& ss, const Charactor& attacker, const Charactor& target, int damage) {
		ss << "player (named: " << attacker.name() << ") attack player(named: " << target.name() << ")\n";
		ss << "== atk valid damage: " << damage << "\n";
		ss << "== remain hp: " << target.getHp() << "/" << target.getMaxHp() << "\n";
	}
}

BattleSystem::BattleSystem(DI di) :log_(di.log)
{
}

void BattleSystem::playBattle(Charactor& player1, Charactor& player2)
{
	bool playerOneFast = isFast(player1, player2);
	Charactor* first = playerOneFast ? &player1 : &player2;
	Charactor* second = playerOneFast ? &player2 : &player1;

	std::stringstream ss;

	int p1ValidDamage = getValidDamage(*first, *second);
	second->takeDamage(p1ValidDamage);
	makeBattleLog(ss, *first, *second, p1ValidDamage);

	if (second->isAlive()) {
		int p2ValidDamage = getValidDamage(*first, *second);
		first->takeDamage(p2ValidDamage);
		makeBattleLog(ss, *second, *first, p2ValidDamage);
	}

	log_.log(ss.str());
}

bool BattleSystem::isFast(const Charactor& player1, const Charactor& player2)
{
	if (player1.getSpeed() != player2.getSpeed()) {
		return  player1.getSpeed() > player2.getSpeed();
	}

	if (player1.isPlayable() != player2.isPlayable()) {
		return player1.isPlayable();
	}

	return false;
}

int BattleSystem::getValidDamage(const Charactor& attacker, const Charactor& target)
{
	int damage = attacker.getAttack() - target.getDefense();
	damage = damage > 0 ? damage : 1;
	return damage;
}

