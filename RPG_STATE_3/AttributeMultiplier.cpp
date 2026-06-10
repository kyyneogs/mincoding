#include "AttributeMultiplier.h"

AttributeMultiplier::AttributeMultiplier()
{
	multiplyMap_ = { {
	{{1.0, 1.5, 1.0, 0.5}},
	{{0.5, 1.0, 1.5, 1.0}},
	{{1.0, 0.5, 1.0, 1.5}},
	{{1.5, 1.0, 0.5, 1.0}}
} };
}

float AttributeMultiplier::getMultiplier(AttributeType from, AttributeType to)
{
	return multiplyMap_[static_cast<std::size_t>(from)][static_cast<std::size_t>(to)];
}
