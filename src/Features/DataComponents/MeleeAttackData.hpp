#ifndef MELEEATTACKDATA_HPP
#define MELEEATTACKDATA_HPP

#include <memory>
#include "Core/DataComponents/IDataComponent.hpp"
#include "Core/FightSystem/ITargetSelectorStrategy.hpp"

struct MeleeAttackData : public IDataComponent
{
    static const int DefaultPriority = 20;
    int damage;
    int range;
    std::shared_ptr<ITargetSelectorStrategy> targetSelector;
    int priority;

    MeleeAttackData(int damage_, int range_, std::shared_ptr<ITargetSelectorStrategy> _targetSelector,
                    int priority_ = DefaultPriority )
        : damage(damage_), range(range_), targetSelector(_targetSelector), priority(priority_)
    {

    }
};

#endif // MELEEATTACKDATA_HPP
