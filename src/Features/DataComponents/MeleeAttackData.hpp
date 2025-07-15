#ifndef MELEEATTACKDATA_HPP
#define MELEEATTACKDATA_HPP

#include "Core/DataComponents/IDataComponent.hpp"
#include "Core/FightSystem/ITargetSelectorStrategy.hpp"

#include <memory>

struct MeleeAttackData : public IDataComponent
{
	int damage;
	int range;
	std::shared_ptr<ITargetSelectorStrategy> targetSelector;

	MeleeAttackData(int damage_, int range_, std::shared_ptr<ITargetSelectorStrategy> _targetSelector) :
			damage(damage_),
			range(range_),
			targetSelector(_targetSelector)
	{}
};

#endif	// MELEEATTACKDATA_HPP
