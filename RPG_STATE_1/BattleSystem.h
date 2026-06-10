#pragma once

class LogSystem;
class Charactor;

class BattleSystem {
public:
	struct DI {
		LogSystem& log;
	};
	BattleSystem(DI di);
	~BattleSystem() = default;

	// fight until 1 die
	void playBattle(Charactor& player1, Charactor& player2);

private:
	bool isFast(const Charactor& player1, const Charactor& player2);
	int getValidDamage(const Charactor& attacker, const Charactor& target);

	LogSystem& log_;
};