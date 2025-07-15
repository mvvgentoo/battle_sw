#ifndef MELEEATTACKBEHAVIOR_HPP
#define MELEEATTACKBEHAVIOR_HPP

#include "Core/FightSystem/IAttackBehavior.hpp"

#include <memory>

class MeleeAttackBehavior : public IAttackBehavior
{
public:
    const static int DefaultPriority = 50;
    explicit MeleeAttackBehavior(int priority = DefaultPriority);

	int getPriority() const override;
	bool canBeActivated(const EntityManager&, EntityID) const override;

	std::vector<EntityID> findTargets(const EntityManager& entityManager, EntityID self) const override;
    void execute(const IWorldContext& worldContext, EntityID attacker, const std::vector<EntityID>& targets) const override;
private:
    int _priority;
};
#endif	// MELEEATTACKBEHAVIOR_HPP
