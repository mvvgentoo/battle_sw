#ifndef RANGEATTACKBEHAVIOR_HPP
#define RANGEATTACKBEHAVIOR_HPP

#include "Core/FightSystem/CombatSystem.hpp"
#include "Core/FightSystem/IAttackBehavior.hpp"
#include "Features/DataComponents/RangeAttackData.hpp"

#include <memory>

class RangeAttackBehavior : public IAttackBehavior
{
public:
	explicit RangeAttackBehavior(std::shared_ptr<RangeAttackData> data);
	virtual ~RangeAttackBehavior() = default;

	int getPriority() const override;
	bool canBeActivated(const EntityManager&, EntityID) const override;

	std::vector<EntityID> findTargets(const EntityManager& entityManager, EntityID self) const override;
	void execute(EntityID attacker, const std::vector<EntityID>& targets, CombatSystem& combat) const override;

private:
	std::shared_ptr<RangeAttackData> _data;
};
#endif
