#pragma once

#include "AttributeMultiplier.h"
#include "LogSystem.h"
#include "Charactor.h"

class BattleSystem {
public:
	struct DI {
		LogSystem& log;
		AttributeMultiplier& multiplier;
	};
	BattleSystem(DI di);
	~BattleSystem() = default;

	// fight one round; p1UseSkill/p2UseSkill are honored only if MP is sufficient
	void playBattle(Charactor& player1, Charactor& player2, bool p1UseSkill = false, bool p2UseSkill = false);

private:
	bool isFast(const Charactor& player1, const Charactor& player2);
	int calculateValidDamage(const Charactor& attacker, const Charactor& target, float multiply);
	int calculateSkillDamage(Charactor& attacker, const Charactor& target);

	LogSystem& log_;
	AttributeMultiplier& multiplier_;
};