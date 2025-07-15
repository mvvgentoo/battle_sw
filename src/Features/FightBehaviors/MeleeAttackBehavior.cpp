#include "MeleeAttackBehavior.hpp"
#include "Features/DataComponents/MeleeAttackData.hpp"

#include "Core/Systems/EntityManager.hpp"

MeleeAttackBehavior::MeleeAttackBehavior(int priority) : _priority(priority)
{

}

int MeleeAttackBehavior::getPriority() const
{
    return _priority;
}

bool MeleeAttackBehavior::canBeActivated(const EntityManager&, EntityID) const
{
	return true;
}

std::vector<EntityID> MeleeAttackBehavior::findTargets(const EntityManager& entityManager, EntityID self) const
{  
    auto selfEntity = entityManager.getEntityByID(self).lock();
    if (!selfEntity)
    {
        return {};
    }

    auto data = selfEntity->getComponentByType<MeleeAttackData>();
    if (!data || !data->targetSelector)
    {
        return {};
    }

    Position pos = selfEntity->getPosition();

    return data->targetSelector->selectTargets(entityManager.getNeighboursInRadius(
		pos,
        [range = data->range, self](const auto& entity, Position pos)
		{
			return entity && entity->isAlive() && entity->getID() != self
				   && chebyshevDistance(pos, entity->getPosition()) <= range;
		}));
}

void MeleeAttackBehavior::execute(const EntityManager& entityManager, EntityID attacker, const std::vector<EntityID>& targets, CombatSystem& combat) const
{
    auto attackerHandle = entityManager.getEntityByID(attacker);
    if (auto attackerEntity = attackerHandle.lock())
    {
        auto data = attackerEntity->getComponentByType<MeleeAttackData>();
        for (auto id : targets)
        {
            combat.dealDamageNow({attacker, id, data->damage});
        }
    }
}
