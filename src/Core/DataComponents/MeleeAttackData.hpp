#ifndef MELEEATTACKDATA_HPP
#define MELEEATTACKDATA_HPP

#include <memory>
#include "Core/BaseTypes.hpp"
#include "Core/FightSystem/ITargetSelectorStrategy.hpp"

struct MeleeAttackData : public IDataComponent
{
    int damage = 10;
    int range = 1;
    int priority = 20;
    std::shared_ptr<ITargetSelectorStrategy> targetSelector;
};

#endif // MELEEATTACKDATA_HPP
