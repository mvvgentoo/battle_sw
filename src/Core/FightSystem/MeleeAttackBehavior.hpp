#ifndef MELEEATTACKBEHAVIOR_HPP
#define MELEEATTACKBEHAVIOR_HPP

#include <memory>
#include "Core/FightSystem/IAttackBehavior.hpp"
#include "Core/DataComponents/MeleeAttackData.hpp"

#include "Core/World.hpp"
#include "Core/FightSystem/CombatSystem.hpp"

class MeleeAttackBehavior : public IAttackBehavior
{
public:
    explicit MeleeAttackBehavior(std::shared_ptr<MeleeAttackData> data);

    int getPriority() const override;

    bool canBeActivated(const World&, EntityID) const override {
        return true; // всегда можно
    }

    std::vector<EntityID> findTargets(const World& world, EntityID self) const override {
        const Position& pos = world.getEntityByID(self).lock()->getPosition();
        return _data->targetSelector->selectTargets
        (
            world.getNeighboursInRadius(pos, [range = _data->range](const auto& entity, Position pos) {
                return entity && entity->isAlive()
                       && Grid::chebyshevDistance(pos, entity->getPosition()) <= range;
            })
        );
    }

    void execute(EntityID attacker, const std::vector<EntityID>& targets, CombatSystem& combat) const override {
        for (auto id : targets) {
            combat.dealDamageNow({ attacker, id, _data->damage });
        }
    }

private:
    std::shared_ptr<MeleeAttackData> _data;
};
#endif // MELEEATTACKBEHAVIOR_HPP
