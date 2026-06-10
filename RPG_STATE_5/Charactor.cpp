#include "Charactor.h"

Weapon Charactor::defaultWeapon_ = Weapon{ "hand" , 0 };
Sheild Charactor::defaultSheild_ = Sheild{ "hand" , 0 };


Charactor::Charactor(std::size_t uniqueIndex, const std::string& name, std::size_t id, int maxHp, int attack, int defense, int speed,
	int exp, int level, AttributeType type, Inventory& inventory, bool playable, JobType job)
	: uniqueIndex_(uniqueIndex), name_(name), id_(id),
	type_(type), job_(job), jobData_(getJobData(job)),
	playable_(playable),
	maxHp_(maxHp + jobData_.bonusHp), hp_(maxHp + jobData_.bonusHp),
	attack_(attack + jobData_.bonusAttack), defense_(defense + jobData_.bonusDefense), speed_(speed),
	exp_(exp), level_(level),
	mp_(jobData_.maxMp), maxMp_(jobData_.maxMp),
	weapon_(defaultWeapon_), sheild_(defaultSheild_), inventory_(inventory)
{
}

const std::string& Charactor::name() const
{
	return name_;
}

bool Charactor::isPlayable() const
{
	return playable_;
}

std::size_t Charactor::index() const
{
	return uniqueIndex_;
}

int Charactor::getAttack() const
{
	return attack_ + weapon_.attack;
}

int Charactor::getDefense() const
{
	return defense_ + sheild_.defense;
}

int Charactor::getHp() const
{
	return hp_;
}

int Charactor::getMaxHp() const
{
	return maxHp_;
}

int Charactor::getSpeed() const
{
	return speed_;
}

int Charactor::getExp() const
{
	return exp_;
}

int Charactor::getLevel() const
{
	return level_;
}

AttributeType Charactor::getType() const
{
	return type_;
}

JobType Charactor::getJob() const
{
	return job_;
}

int Charactor::getMp() const
{
	return mp_;
}

int Charactor::getMaxMp() const
{
	return maxMp_;
}

bool Charactor::canUseSkill() const
{
	if (job_ == JobType::None) return false;
	return mp_ >= jobData_.skill.mpCost;
}

bool Charactor::useSkill()
{
	if (!canUseSkill()) return false;
	mp_ -= jobData_.skill.mpCost;
	return true;
}

void Charactor::restoreMp(int amount)
{
	mp_ += amount;
	if (mp_ > maxMp_) mp_ = maxMp_;
}

const Skill* Charactor::getSkill() const
{
	if (job_ == JobType::None) return nullptr;
	return &jobData_.skill;
}

void Charactor::takeDamage(int damage)
{
	hp_ -= damage;
	hp_ = hp_ > 0 ? hp_ : 0;
}

bool Charactor::isAlive() const
{
	return hp_ > 0;
}

void Charactor::equipWeapon(const Weapon& weapon)
{
	weapon_ = weapon;
}

void Charactor::unequipWeapon()
{
	weapon_ = defaultWeapon_;
}

void Charactor::equipSheild(const Sheild& sheild)
{
	sheild_ = sheild;
}

void Charactor::unequipSheild()
{
	sheild_ = defaultSheild_;
}

const Weapon& Charactor::getEquipWeapon() const
{
	return weapon_;
}

const Sheild& Charactor::getEquipSheild() const
{
	return sheild_;
}

Inventory& Charactor::getInventory()
{
	return inventory_;
}

const Inventory& Charactor::getInvenory() const
{
	return inventory_;
}

void Charactor::addExp(int exp)
{
	exp_ += exp;
}

void Charactor::levelUp()
{
	++level_;
}
