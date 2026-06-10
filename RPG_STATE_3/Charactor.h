#pragma once

#include <string>
#include "Weapon.h"
#include "AttributeType.h"
#include "Inventory.h"

class Charactor {
public:
	Charactor(const std::string& name, std::size_t id, int maxHp, int attack, int defense, int speed, AttributeType type, Inventory& inventory, bool playable);
	~Charactor() = default;

	const std::string& name() const;
	bool isPlayable() const;

	int getAttack() const;
	int getDefense() const;
	int getHp() const;
	int getMaxHp() const;
	int getSpeed() const;
	AttributeType getType() const;

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

private:
	static Weapon defaultWeapon_;
	static Sheild defaultSheild_;
	std::string name_;
	std::size_t id_;
	AttributeType type_;
	Weapon weapon_;
	Sheild sheild_;
	bool playable_;
	int maxHp_;
	int hp_;
	int attack_;
	int defense_;
	int speed_;
	Inventory& inventory_;
};
