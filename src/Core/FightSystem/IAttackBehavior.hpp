#ifndef IATTACKBEHAVIOR_HPP
#define IATTACKBEHAVIOR_HPP

#include "Core/Utils/BaseTypes.hpp"

#include <vector>

class EntityManager;
class CombatSystem;

class IAttackBehavior
{
public:
	virtual ~IAttackBehavior() = default;

	virtual int getPriority() const = 0;
	virtual bool canBeActivated(const EntityManager&, EntityID) const = 0;

	virtual std::vector<EntityID> findTargets(const EntityManager&, EntityID) const = 0;
    virtual void execute(const EntityManager& entityManager, EntityID attacker, const std::vector<EntityID>& targets, CombatSystem& combatSystem) const = 0;
};

#endif	// IATTACKBEHAVIOR_HPP
