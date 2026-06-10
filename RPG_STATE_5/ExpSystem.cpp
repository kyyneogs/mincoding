#include "ExpSystem.h"

ExpSystem::ExpSystem(DI di) : log_(di.log)
{
}

void ExpSystem::calculateLevelUp(Charactor& charactor)
{
	while (true) {
		int maxCut = charactor.getExp() / 200;
		if (maxCut > charactor.getLevel()) {
			charactor.levelUp();
			log_.log("level up to " + std::to_string(charactor.getLevel()));
		}
		else {
			break;
		}
	}
}