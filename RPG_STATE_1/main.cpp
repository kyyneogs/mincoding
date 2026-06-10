#include "BattleSystem.h"
#include "LogSystem.h"
#include "Charactor.h"

int main() {
	LogSystem log;
	BattleSystem battleSystem({ log });
	Charactor player1("OKS", 1, 100, 10, 5, 7, true);
	Charactor monster("Goblin", 2, 60, 4, 2, 3, false);

	while (player1.isAlive() && monster.isAlive()) {
		battleSystem.playBattle(player1, monster);
	}


	return 0;
}