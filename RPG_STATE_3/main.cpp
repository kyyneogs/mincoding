#include "BattleSystem.h"
#include "LogSystem.h"
#include "Charactor.h"
#include "RootingTable.h"

int main() {
	LogSystem log;
	AttributeMultiplier multiply;
	RootingTable rootTable;
	BattleSystem battleSystem({ log, multiply });
	Inventory player1Inventory(100);
	Inventory monsterInventory(5);
	rootTable.createGoblinRootInventory(monsterInventory);

	Charactor player1("OKS", 1, 100, 10, 5, 7, AttributeType::Ground, player1Inventory, true);
	Charactor monster("Goblin", 2, 60, 4, 2, 3, AttributeType::Fire, monsterInventory, false);

	Weapon userWeapon = { "초보자 활", 5 };
	Sheild userSheild = { "초보자 방패", 5 };
	player1.equipWeapon(userWeapon);
	player1.equipSheild(userSheild);

	Weapon monsterWeapon = { "고블린 단검", 2 };
	Sheild monsterSheild = { "고블린 방패", 1 };
	monster.equipWeapon(monsterWeapon);
	monster.equipSheild(monsterSheild);

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

			const auto& items = monster.getInvenory().showInventory();
			log.log(":::root item list (total " + std::to_string(items.size()) + "):::");
			for (std::size_t i = 0;i < items.size(); ++i) {
				log.log(items[i].name);
			}
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