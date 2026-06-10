#pragma once

#include <string>

enum class SkillEffect {
	DamageMultiplier,   // attack * (power / 100.0), normal defense applies
	FixedDamage,        // fixed power damage, ignores defense
	PiercingMultiplier, // attack * (power / 100.0), half defense
};

struct Skill {
	std::string name;
	int power;
	int mpCost;
	SkillEffect effect;
};
