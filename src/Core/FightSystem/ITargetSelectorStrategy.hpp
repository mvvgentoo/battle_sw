#ifndef ITARGETSELECTORSTRATEGY_HPP
#define ITARGETSELECTORSTRATEGY_HPP

#include "Core/Utils/BaseTypes.hpp"

#include <vector>

class ITargetSelectorStrategy
{
public:
	ITargetSelectorStrategy();
	virtual std::vector<EntityID> selectTargets(const std::vector<EntityID>& initialTargets) = 0;
};

class RandomTargetSelector : public ITargetSelectorStrategy
{
public:
	RandomTargetSelector();
	std::vector<EntityID> selectTargets(const std::vector<EntityID>& initialTargets);
};

#endif	// ITARGETSELECTORSTRATEGY_HPP
