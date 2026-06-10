#pragma once

#include <map>
#include <array>

#include "AttributeType.h"

class AttributeMultiplier {
public:
	static float getMultiplier(AttributeType from, AttributeType to);

private:
	AttributeMultiplier() = delete;
	~AttributeMultiplier() = delete;
	static std::array<std::array<float, 4>, 4> multiplyMap_;
};
