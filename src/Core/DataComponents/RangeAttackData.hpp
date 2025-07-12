#ifndef RANGEATTACKDATA_HPP
#define RANGEATTACKDATA_HPP

#include <memory>
#include "Core/BaseTypes.hpp"
#include "Core/FightSystem/ITargetSelectorStrategy.hpp"

struct RangeAttackData : public IDataComponent
{
    int agility = 10;
    int rangeMin = 2;
    int rangeMax = 5;
    int priority = 30;
    std::shared_ptr<ITargetSelectorStrategy> targetSelector;
};

#endif // RANGEATTACKDATA_HPP
