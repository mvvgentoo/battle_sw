#include "MeleeAttackBehavior.hpp"
#include "Core/Systems/EntityManager.hpp"

MeleeAttackBehavior::MeleeAttackBehavior(std::shared_ptr<MeleeAttackData> data)
    : _data(std::move(data)) {}

int MeleeAttackBehavior::getPriority() const
{
    return _data->priority;
}

bool MeleeAttackBehavior::canBeActivated(const EntityManager &, EntityID) const
{
    return true;
}

std::vector<EntityID> MeleeAttackBehavior::findTargets(const EntityManager &entityManager, EntityID self) const
{
    const Position& pos = entityManager.getEntityByID(self).lock()->getPosition();
    return _data->targetSelector->selectTargets
        (
            entityManager.getNeighboursInRadius(pos, [range = _data->range](const auto& entity, Position pos) {
                return entity && entity->isAlive()
                       && chebyshevDistance(pos, entity->getPosition()) <= range;
            })
            );
}

void MeleeAttackBehavior::execute(EntityID attacker, const std::vector<EntityID> &targets, CombatSystem &combat) const
{
    for (auto id : targets)
    {
        combat.dealDamageNow({ attacker, id, _data->damage });
    }
}
