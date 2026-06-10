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

	// fight until 1 die
	void playBattle(Charactor& player1, Charactor& player2);

private:
	bool isFast(const Charactor& player1, const Charactor& player2);
	int calculateValidDamage(const Charactor& attacker, const Charactor& target, float multiply);

	LogSystem& log_;
	AttributeMultiplier& multiplier_;
};