#ifndef RANGEATTACKDATA_HPP
#define RANGEATTACKDATA_HPP

#include "Core/DataComponents/IDataComponent.hpp"
#include "Core/FightSystem/ITargetSelectorStrategy.hpp"

#include <memory>

struct RangeAttackData : public IDataComponent
{
	int agility;
	int rangeMin;
	int rangeMax;
	std::shared_ptr<ITargetSelectorStrategy> targetSelector;

	RangeAttackData(
		int agility_, int rangeMin_, int rangeMax_, std::shared_ptr<ITargetSelectorStrategy> targetSelector_) :
			agility(agility_),
			rangeMin(rangeMin_),
			rangeMax(rangeMax_),
			targetSelector(targetSelector_)
	{}
};

#endif	// RANGEATTACKDATA_HPP
