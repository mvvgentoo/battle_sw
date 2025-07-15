#ifndef RANGEATTACKBEHAVIOR_HPP
#define RANGEATTACKBEHAVIOR_HPP

#include "Core/FightSystem/IAttackBehavior.hpp"

class IWorldContext;
class EntityManager;

#include <memory>

class RangeAttackBehavior : public IAttackBehavior
{
public:
    const static int DefaultPriority = 100;
    explicit RangeAttackBehavior(int priority = DefaultPriority);
	virtual ~RangeAttackBehavior() = default;

	int getPriority() const override;
	bool canBeActivated(const EntityManager&, EntityID) const override;

	std::vector<EntityID> findTargets(const EntityManager& entityManager, EntityID self) const override;
    void execute(const IWorldContext& worldContext, EntityID attacker, const std::vector<EntityID>& targets) const override;

private:
    int _priority;
};
#endif
