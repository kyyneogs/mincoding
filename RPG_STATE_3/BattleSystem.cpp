#include "BattleSystem.h"

#include "LogSystem.h"
#include "Charactor.h"
#include "AttributeMultiplier.h"

#include <sstream>

namespace {
	std::string enumToString(AttributeType type) {
		switch (type) {
		case AttributeType::Fire: return "Fire";
		case AttributeType::Leaf: return "Leaf";
		case AttributeType::Ice: return "Ice";
		case AttributeType::Ground: return "Ground";
		}
		return "";
	}

	void makeBattleLog(std::stringstream& ss, const Charactor& attacker, const Charactor& target, int damage, float multiple) {
		bool weakAttack = multiple <= 0.5f;
		bool strongAttack = multiple >= 1.5f;
		ss << "player (named: " << attacker.name() << ", type:" << enumToString(attacker.getType()) << 
			") attack player(named: " << target.name() << ", type:" << enumToString(target.getType()) << ")";
		ss << "\n== atk valid damage: " << damage << " (weapon: " << attacker.getEquipWeapon().name << ")";
		if (strongAttack) {
			ss << " (효과는 굉장했다!)";
		}
		if (weakAttack) {
			ss << " (효과는 미비했다)";
		}
		ss << "\n== remain hp: " << target.getHp() << "/" << target.getMaxHp() << " (sheild: " << target.getEquipSheild().name << ")";;

		if (!target.isAlive()) {
			ss << "\n== player(" << target.name() << ") is slained";
		}
		if (!attacker.isAlive()) {
			ss << "\n== player(" << attacker.name() << ") is slained";
		}
	}
}

BattleSystem::BattleSystem(DI di) :log_(di.log), multiplier_(di.multiplier)
{
}

void BattleSystem::playBattle(Charactor& player1, Charactor& player2)
{
	bool playerOneFast = isFast(player1, player2);
	Charactor* first = playerOneFast ? &player1 : &player2;
	Charactor* second = playerOneFast ? &player2 : &player1;

	std::stringstream ss;

	float multiply = multiplier_.getMultiplier(first->getType(), second->getType());
	int p1ValidDamage = calculateValidDamage(*first, *second, multiply);
	second->takeDamage(p1ValidDamage);
	makeBattleLog(ss, *first, *second, p1ValidDamage, multiply);

	if (second->isAlive()) {
		ss << "\n";
		multiply = multiplier_.getMultiplier(second->getType(), first->getType());
		int p2ValidDamage = calculateValidDamage(*second, *first, multiply);
		first->takeDamage(p2ValidDamage);
		makeBattleLog(ss, *second, *first, p2ValidDamage, multiply);
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

int BattleSystem::calculateValidDamage(const Charactor& attacker, const Charactor& target, float multiply)
{
	int damage = (attacker.getAttack() * multiply) - target.getDefense();
	damage = damage > 0 ? damage : 1;
	return damage;
}

