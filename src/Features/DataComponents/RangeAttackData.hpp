#ifndef RANGEATTACKDATA_HPP
#define RANGEATTACKDATA_HPP

#include <memory>
#include "Core/DataComponents/IDataComponent.hpp"
#include "Core/FightSystem/ITargetSelectorStrategy.hpp"

struct RangeAttackData : public IDataComponent
{
    static const int DefaultPriority = 50;
    int agility;
    int rangeMin;
    int rangeMax;
    std::shared_ptr<ITargetSelectorStrategy> targetSelector;
    int priority;

    RangeAttackData(int agility_, int rangeMin_, int rangeMax_,
                    std::shared_ptr<ITargetSelectorStrategy> targetSelector_, int priority_ = DefaultPriority)
        : agility(agility_), rangeMin(rangeMin_), rangeMax(rangeMax_), targetSelector(targetSelector_), priority(priority_)
    {

    }

};

#endif // RANGEATTACKDATA_HPP
