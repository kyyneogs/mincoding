#pragma once

#include <string>
#include "Weapon.h"
#include "AttributeType.h"
#include "Inventory.h"
#include "Job.h"

class Charactor {
public:
	Charactor(std::size_t uniqueIndex, const std::string& name, std::size_t id, int maxHp, int attack, int defense, int speed,
		int exp, int level, AttributeType type, Inventory& inventory, bool playable, JobType job = JobType::None);
	~Charactor() = default;

	const std::string& name() const;
	bool isPlayable() const;

	std::size_t index() const;
	int getAttack() const;
	int getDefense() const;
	int getHp() const;
	int getMaxHp() const;
	int getSpeed() const;
	int getExp() const;
	int getLevel() const;
	AttributeType getType() const;
	JobType getJob() const;
	int getMp() const;
	int getMaxMp() const;
	bool canUseSkill() const;
	bool useSkill();
	void restoreMp(int amount);
	const Skill* getSkill() const;

	void takeDamage(int damage);
	bool isAlive() const;

	void equipWeapon(const Weapon& weapon);
	void unequipWeapon();

	void equipSheild(const Sheild& sheild);
	void unequipSheild();

	const Weapon& getEquipWeapon() const;
	const Sheild& getEquipSheild() const;

	Inventory& getInventory();
	const Inventory& getInvenory() const;

	void addExp(int exp);
	void levelUp();

private:
	static Weapon defaultWeapon_;
	static Sheild defaultSheild_;
	const std::size_t uniqueIndex_;
	std::string name_;
	std::size_t id_;
	AttributeType type_;
	JobType job_;
	JobData jobData_;
	Weapon weapon_;
	Sheild sheild_;
	bool playable_;
	int maxHp_;
	int hp_;
	int attack_;
	int defense_;
	int speed_;
	int exp_;
	int level_;
	int mp_;
	int maxMp_;
	Inventory& inventory_;
};
