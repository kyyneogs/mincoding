#include "BattleSystem.h"
#include "LogSystem.h"
#include "Charactor.h"

int main() {
	LogSystem log;
	BattleSystem battleSystem({ log });
	Charactor player1("OKS", 1, 100, 10, 5, 7, AttributeType::Ground, true);
	Charactor monster("Goblin", 2, 60, 4, 2, 3, AttributeType::Fire, false);

	int i = 0;
	log.log("=== match up start ===");
	while (player1.isAlive() && monster.isAlive()) {
		log.log("<< turn " + std::to_string(++i) + " >>");
		battleSystem.playBattle(player1, monster);
	}
	log.log("=== match end ===");
	if (player1.isAlive() || monster.isAlive()) {
		if (player1.isAlive()) {
			log.log("winner: " + player1.name());
		}
		else {
			log.log("winner: " + monster.name());
		}
	}
	else {
		log.log("winner: none");
	}


	return 0;
}