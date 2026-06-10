#pragma once

#include "Skill.h"
#include <string>

enum class JobType { None, Warrior, Mage, Archer };

struct JobData {
	std::string name;
	Skill skill;
	int bonusAttack;
	int bonusDefense;
	int bonusHp;
	int maxMp;
};

inline JobData getJobData(JobType job) {
	switch (job) {
	case JobType::Warrior:
		return { "전사", { "강타", 200, 20, SkillEffect::DamageMultiplier }, 3, 2, 20, 40 };
	case JobType::Mage:
		return { "마법사", { "파이어볼", 30, 25, SkillEffect::FixedDamage }, 1, 0, 0, 60 };
	case JobType::Archer:
		return { "궁수", { "관통사격", 150, 15, SkillEffect::PiercingMultiplier }, 2, 1, 10, 50 };
	default:
		return { "없음", { "", 0, 0, SkillEffect::DamageMultiplier }, 0, 0, 0, 0 };
	}
}
