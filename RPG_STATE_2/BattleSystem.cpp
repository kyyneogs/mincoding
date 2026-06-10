#include "BattleSystem.h"

#include "LogSystem.h"
#include "Charactor.h"
#include "AttributeMultiplier.h"

#include <sstream>

namespace {
	void makeBattleLog(std::stringstream& ss, const Charactor& attacker, const Charactor& target, int damage) {
		float muliple = AttributeMultiplier::getMultiplier(attacker.getType(), target.getType());
		bool weakAttack = muliple <= 0.5f;
		bool strongAttack = muliple >= 1.5f;
		ss << "player (named: " << attacker.name() << ") attack player(named: " << target.name() << ")";
		ss << "\n== atk valid damage: " << damage;
		if (strongAttack) {
			ss << " (효과는 굉장했다!)";
		}
		if (weakAttack) {
			ss << " (효과는 미비했다)";
		}
		ss << "\n== remain hp: " << target.getHp() << "/" << target.getMaxHp();

		if (!target.isAlive()) {
			ss << "\n== player(" << target.name() << ") is slained";
		}
		if (!attacker.isAlive()) {
			ss << "\n== player(" << attacker.name() << ") is slained";
		}
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
		int p2ValidDamage = getValidDamage(*second, *first);
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
	const float multiply = AttributeMultiplier::getMultiplier(attacker.getType(), target.getType());
	int damage = (attacker.getAttack() * multiply) - target.getDefense();
	damage = damage > 0 ? damage : 1;
	return damage;
}

