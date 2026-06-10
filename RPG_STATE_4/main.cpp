#include "BattleSystem.h"
#include "LogSystem.h"
#include "Charactor.h"
#include "RootingTable.h"
#include "Dungeon.h"
#include "MonsterSpawnSystem.h"
#include "ExpSystem.h"

#include <iostream>

class App {
public:
	App()
		: battleSystem({ log, multiply }), playerInventory(100),
		player(0, "OKS", 1, 100, 10, 5, 7, 0, 0, AttributeType::Ground, playerInventory, true),
		spawnSystem({ log, rootTable }), dungeon("고블린"), expSystem({ log }) {
		Weapon userWeapon = { "초보자 활", 5 };
		Sheild userSheild = { "초보자 방패", 5 };
		player.equipWeapon(userWeapon);
		player.equipSheild(userSheild);
	}

	void start() {
		while (1) {
			int command;
			log.log("뭘 하고 싶지? 1: 던전 2: 숨쉬기");
			std::cin >> command;

			switch (command) {
			case 1:
				enterDungeon();
				break;
			case 2:
				log.log("열심히 쉬었다 ...");
				break;
			default:
				break;
			}

			if (!player.isAlive()) break;
		}
	}

private:
	void enterDungeon() {
		// todo: 전면적인 리팩토링이 필요해보임.
		{
			auto monsterList = spawnSystem.spawnMonster();

			for (std::size_t i = 0; i < monsterList.size(); ++i) {
				dungeon.addMonster(monsterList[i]);
			}

			log.log("던전 " + dungeon.name() + " 에 입장하였다 ...");
			log.log(std::to_string(monsterList.size()) + " 마리의 몬스터가 보인다 ...");
		}

		auto& dungeonMonsters = dungeon.getMonsterList();

		for (std::size_t i = 0; i < dungeonMonsters.size(); ++i) {
			auto* monster = spawnSystem.getMonster(dungeonMonsters[i]);
			if (monster) {
				log.log("몬스터 (named: " + monster->name() + ") 를 조우하였다.");
				log.log("어떤 행동을 취할것인가? 1: 싸움 2: 도망");
				while (true) {
					int inputValue;
					std::cin >> inputValue;

					bool inputValid = true;
					switch (inputValue) {
					case 1:
						matchUp(player, *monster);
						if (!player.isAlive()) {
							log.log("당신은 사망했다.");
							return;
						}
						break;
					case 2:
						break;
					default:
						inputValid = false;
						break;
					}

					if (inputValid) {
						break;
					}
				}
			}
		}

		for (std::size_t i = 0; i < dungeonMonsters.size(); ++i) {
			spawnSystem.releaseMonster(dungeonMonsters[i]);
		}

		dungeon.clearMonster();
	}

	void matchUp(Charactor& p1, Charactor& p2) {
		int i = 0;
		log.log("======= 싸움을 시작합니다 ========");
		while (p1.isAlive() && p2.isAlive()) {
			log.log("------ " + std::to_string(++i) + " 번째 턴 ------");
			battleSystem.playBattle(p1, p2);
		}
		log.log("======= 싸움을 종료합니다 =======");
		if (p1.isAlive() || p2.isAlive()) {
			if (p1.isAlive()) {
				log.log("승리자: " + p1.name());

				if (p1.isPlayable()) {
					auto exp = p2.getExp();
					log.log("얻은 경험치: " + std::to_string(exp));
					p1.addExp(exp);
					expSystem.calculateLevelUp(p1);

					const auto& items = p2.getInvenory().showInventory();
					log.log(" --- 드랍 아이템 (총 갯수 " + std::to_string(items.size()) + ") ---");
					for (std::size_t i = 0;i < items.size(); ++i) {
						log.log(items[i].name);
					}
					log.log("----------------------------");
				}
			}
			else {
				log.log("승리자: " + p2.name());
			}
		}
		else {
			log.log("승리자: 없음");
		}
	}
	LogSystem log;
	RootingTable rootTable;
	BattleSystem battleSystem;
	Dungeon dungeon;
	MonsterSpawnSystem spawnSystem;
	ExpSystem expSystem;

	AttributeMultiplier multiply;
	Inventory playerInventory;
	Charactor player;
};

int main() {
	App app;

	app.start();
	return 0;
}