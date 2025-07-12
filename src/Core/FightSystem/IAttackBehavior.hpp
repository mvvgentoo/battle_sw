#ifndef IATTACKBEHAVIOR_HPP
#define IATTACKBEHAVIOR_HPP

#include <vector>
#include "Core/BaseTypes.hpp"


class World;
class CombatSystem;

class IAttackBehavior {
public:
    virtual ~IAttackBehavior() = default;

    virtual int getPriority() const = 0;
    virtual bool canBeActivated(const World&, EntityID) const = 0;

    virtual std::vector<EntityID> findTargets(const World&, EntityID) const = 0;
    virtual void execute(EntityID attacker, const std::vector<EntityID>& targets, CombatSystem& combatSystem) const = 0;
};

#endif // IATTACKBEHAVIOR_HPP
