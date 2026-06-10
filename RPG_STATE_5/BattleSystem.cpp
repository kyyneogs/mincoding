#include "BattleSystem.h"

#include "LogSystem.h"
#include "Charactor.h"
#include "AttributeMultiplier.h"
#include "Skill.h"

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
		ss << attacker.name() << " [" << enumToString(attacker.getType()) << "]"
			<< " -> " << target.name() << " [" << enumToString(target.getType()) << "]";
		ss << "\n   피해량: " << damage << " (무기: " << attacker.getEquipWeapon().name << ")";
		if (strongAttack) {
			ss << " (효과적이었다!)";
		}
		if (weakAttack) {
			ss << " (효과가 미미했다)";
		}
		ss << "\n   남은 HP: " << target.getHp() << "/" << target.getMaxHp()
			<< " (방어구: " << target.getEquipSheild().name << ")";

		if (!target.isAlive()) {
			ss << "\n== " << target.name() << " 이(가) 쓰러졌다!";
		}
	}

	void makeSkillLog(std::stringstream& ss, const Charactor& attacker, const Charactor& target, int damage, const Skill& skill) {
		ss << attacker.name() << " 의 스킬 [" << skill.name << "]!"
			<< " -> " << target.name();
		ss << "\n   스킬 피해량: " << damage;
		ss << "\n   남은 HP: " << target.getHp() << "/" << target.getMaxHp();
		if (!target.isAlive()) {
			ss << "\n   " << target.name() << " 이(가) 쓰러졌다!";
		}
	}
}

BattleSystem::BattleSystem(DI di) :log_(di.log), multiplier_(di.multiplier)
{
}

void BattleSystem::playBattle(Charactor& player1, Charactor& player2, bool p1UseSkill, bool p2UseSkill)
{
	bool playerOneFast = isFast(player1, player2);
	Charactor* first = playerOneFast ? &player1 : &player2;
	Charactor* second = playerOneFast ? &player2 : &player1;

	bool firstUseSkill = (playerOneFast ? p1UseSkill : p2UseSkill);
	bool secondUseSkill = (playerOneFast ? p2UseSkill : p1UseSkill);

	std::stringstream ss;

	bool firstUsedSkill = (firstUseSkill && first->canUseSkill());
	int p1ValidDamage;
	const Skill* firstSkill = first->getSkill();
	if (firstUsedSkill) {
		p1ValidDamage = calculateSkillDamage(*first, *second);
	}
	else {
		float multiply = multiplier_.getMultiplier(first->getType(), second->getType());
		p1ValidDamage = calculateValidDamage(*first, *second, multiply);
	}
	second->takeDamage(p1ValidDamage);
	if (firstUsedSkill && firstSkill) {
		makeSkillLog(ss, *first, *second, p1ValidDamage, *firstSkill);
	}
	else {
		float multiply = multiplier_.getMultiplier(first->getType(), second->getType());
		makeBattleLog(ss, *first, *second, p1ValidDamage, multiply);
	}

	if (second->isAlive()) {
		ss << "\n";
		bool secondUsedSkill = (secondUseSkill && second->canUseSkill());
		const Skill* secondSkill = second->getSkill();
		int p2ValidDamage;
		if (secondUsedSkill) {
			p2ValidDamage = calculateSkillDamage(*second, *first);
		}
		else {
			float multiply = multiplier_.getMultiplier(second->getType(), first->getType());
			p2ValidDamage = calculateValidDamage(*second, *first, multiply);
		}
		first->takeDamage(p2ValidDamage);
		if (secondUsedSkill && secondSkill) {
			makeSkillLog(ss, *second, *first, p2ValidDamage, *secondSkill);
		}
		else {
			float multiply = multiplier_.getMultiplier(second->getType(), first->getType());
			makeBattleLog(ss, *second, *first, p2ValidDamage, multiply);
		}
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

int BattleSystem::calculateSkillDamage(Charactor& attacker, const Charactor& target)
{
	const Skill* skill = attacker.getSkill();
	if (!skill) return 1;

	attacker.useSkill();

	int damage = 1;
	switch (skill->effect) {
	case SkillEffect::DamageMultiplier:
		damage = static_cast<int>(attacker.getAttack() * (skill->power / 100.0f)) - target.getDefense();
		break;
	case SkillEffect::FixedDamage:
		damage = skill->power;
		break;
	case SkillEffect::PiercingMultiplier:
		damage = static_cast<int>(attacker.getAttack() * (skill->power / 100.0f)) - target.getDefense() / 2;
		break;
	}
	return damage > 0 ? damage : 1;
}

