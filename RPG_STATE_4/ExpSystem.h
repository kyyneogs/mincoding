#pragma once

#include "Charactor.h"
#include "LogSystem.h"

class ExpSystem {
public:
	struct DI { LogSystem& log; };
	ExpSystem(DI di);
	~ExpSystem() = default;

	void calculateLevelUp(Charactor& charactor);
private:
	LogSystem& log_;
};