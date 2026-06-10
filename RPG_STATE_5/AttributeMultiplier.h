#pragma once

#include <map>
#include <array>

#include "AttributeType.h"

class AttributeMultiplier {
public:
	AttributeMultiplier();
	float getMultiplier(AttributeType from, AttributeType to);

private:
	std::array<std::array<float, 4>, 4> multiplyMap_;
};
