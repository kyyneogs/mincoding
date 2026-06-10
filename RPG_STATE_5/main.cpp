#include "BattleSystem.h"
#include "LogSystem.h"
#include "Charactor.h"
#include "Job.h"
#include "RootingTable.h"
#include "Dungeon.h"
#include "MonsterSpawnSystem.h"
#include "ExpSystem.h"

#include <iostream>

class App {
public:
	App()
		: battleSystem({ log, multiply }), playerInventory(100),
		player(0, "OKS", 1, 100, 10, 5, 7, 0, 0, AttributeType::Ground, playerInventory, true, selectJob()),
		spawnSystem({ log, rootTable }), dungeon("던전"), expSystem({ log }) {
		Weapon userWeapon = { "초보자 검", 5 };
		Sheild userSheild = { "초보자 방패", 5 };
		player.equipWeapon(userWeapon);
		player.equipSheild(userSheild);

		auto jobData = getJobData(player.getJob());
		log.log("직업 [" + jobData.name + "] 을(를) 선택했습니다.");
		if (player.getSkill()) {
			log.log("스킬: " + player.getSkill()->name +
				" (MP " + std::to_string(player.getSkill()->mpCost) + " 소모)");
		}
	}

	static JobType selectJob() {
		std::cout << "직업을 선택하세요: 1: 전사  2: 마법사  3: 궁수\n";
		while (true) {
			int input;
			std::cin >> input;
			switch (input) {
			case 1: return JobType::Warrior;
			case 2: return JobType::Mage;
			case 3: return JobType::Archer;
			default: std::cout << "1, 2, 3 중 선택하세요.\n"; break;
			}
		}
	}

	void start() {
		while (1) {
			int command;
			log.log("무엇을 하겠어? 1: 던전  2: 마을");
			std::cin >> command;

			switch (command) {
			case 1:
				enterDungeon();
				break;
			case 2:
				log.log("마을에서 휴식합니다 ...");
				break;
			default:
				break;
			}

			if (!player.isAlive()) break;
		}
	}

private:
	void enterDungeon() {
		{
			auto monsterList = spawnSystem.spawnMonster();
			for (std::size_t i = 0; i < monsterList.size(); ++i) {
				dungeon.addMonster(monsterList[i]);
			}
			log.log("던전 [" + dungeon.name() + "] 에 입장하였습니다 ...");
			log.log(std::to_string(monsterList.size()) + " 마리의 몬스터가 나타났다 ...");
		}

		auto& dungeonMonsters = dungeon.getMonsterList();

		for (std::size_t i = 0; i < dungeonMonsters.size(); ++i) {
			auto* monster = spawnSystem.getMonster(dungeonMonsters[i]);
			if (monster) {
				log.log("몬스터 (named: " + monster->name() + ") 와 조우하였다.");
				log.log("어떤 행동을 취하겠는가? 1: 전투 2: 도망");
				while (true) {
					int inputValue;
					std::cin >> inputValue;

					bool inputValid = true;
					switch (inputValue) {
					case 1:
						matchUp(player, *monster);
						if (!player.isAlive()) {
							log.log("플레이어가 사망했다.");
							return;
						}
						break;
					case 2:
						log.log("도망쳤다!");
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

	bool askUseSkill(const Charactor& p) {
		const Skill* skill = p.getSkill();
		if (!skill || p.getMp() <= 0) {
			return false;
		}

		log.log("[HP: " + std::to_string(p.getHp()) + "/" + std::to_string(p.getMaxHp()) +
			"  MP: " + std::to_string(p.getMp()) + "/" + std::to_string(p.getMaxMp()) + "]");

		if (p.canUseSkill()) {
			log.log("행동 선택: 1: 일반 공격  2: " + skill->name +
				" (MP " + std::to_string(skill->mpCost) + " 소모)");
			while (true) {
				int input;
				std::cin >> input;
				if (input == 1) return false;
				if (input == 2) return true;
			}
		}
		else {
			log.log("MP 부족으로 스킬 사용 불가 (현재 MP: " + std::to_string(p.getMp()) + ")");
			return false;
		}
	}

	void matchUp(Charactor& p1, Charactor& p2) {
		int round = 0;
		log.log("======= 전투가 시작됩니다 ========");
		while (p1.isAlive() && p2.isAlive()) {
			log.log("------ " + std::to_string(++round) + " 번째 턴 ------");

			bool p1UseSkill = false;
			if (p1.isPlayable()) {
				p1UseSkill = askUseSkill(p1);
			}

			battleSystem.playBattle(p1, p2, p1UseSkill, false);

			// 매 라운드마다 MP 소량 회복
			if (p1.isPlayable()) {
				p1.restoreMp(5);
			}
		}
		log.log("======= 전투가 종료됩니다 =======");

		if (p1.isAlive() || p2.isAlive()) {
			if (p1.isAlive()) {
				log.log("승리자: " + p1.name());

				if (p1.isPlayable()) {
					auto exp = p2.getExp();
					log.log("획득 경험치: " + std::to_string(exp));
					p1.addExp(exp);
					expSystem.calculateLevelUp(p1);

					const auto& items = p2.getInvenory().showInventory();
					log.log(" --- 드롭 아이템 (총 개수 " + std::to_string(items.size()) + ") ---");
					for (std::size_t i = 0; i < items.size(); ++i) {
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
