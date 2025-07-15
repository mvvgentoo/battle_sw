#ifndef MELEEATTACKBEHAVIOR_HPP
#define MELEEATTACKBEHAVIOR_HPP

#include <memory>
#include "Core/FightSystem/IAttackBehavior.hpp"
#include "Core/FightSystem/CombatSystem.hpp"
#include "Features/DataComponents/MeleeAttackData.hpp"

class MeleeAttackBehavior : public IAttackBehavior
{
public:
    explicit MeleeAttackBehavior(std::shared_ptr<MeleeAttackData> data);

    int getPriority() const override;
    bool canBeActivated(const EntityManager&, EntityID) const override;

    std::vector<EntityID> findTargets(const EntityManager& entityManager, EntityID self) const override;
    void execute(EntityID attacker, const std::vector<EntityID>& targets, CombatSystem& combat) const override;

private:
    std::shared_ptr<MeleeAttackData> _data;
};
#endif // MELEEATTACKBEHAVIOR_HPP
