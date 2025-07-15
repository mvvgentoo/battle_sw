#include "RangeAttackBehavior.hpp"

#include "Core/Systems/EntityManager.hpp"
#include "Features/DataComponents/RangeAttackData.hpp"

RangeAttackBehavior::RangeAttackBehavior(int priority): _priority(priority)
{

}

int RangeAttackBehavior::getPriority() const
{
    return _priority;
}

bool RangeAttackBehavior::canBeActivated(const EntityManager&, EntityID) const
{
	return true;
}

std::vector<EntityID> RangeAttackBehavior::findTargets(const EntityManager& entityManager, EntityID self) const
{
    auto selfEntity = entityManager.getEntityByID(self).lock();
    if (!selfEntity)
    {
        return {};
    }

    auto data = selfEntity->getComponentByType<RangeAttackData>();
    if (!data || !data->targetSelector)
    {
        return {};
    }

    const Position& pos = selfEntity->getPosition();

    return data->targetSelector->selectTargets(entityManager.getNeighboursInRadius(
		pos,
        [rMin = data->rangeMin, rMax = data->rangeMax, self](const auto& entity, Position pos)
		{
			auto dist = chebyshevDistance(pos, entity->getPosition());
			return entity && entity->isAlive() && entity->getID() != self && dist <= rMax && dist >= rMin;
		}));
}

void RangeAttackBehavior::execute(const EntityManager &entityManager, EntityID attacker, const std::vector<EntityID>& targets, CombatSystem& combat) const
{
    auto attackerHandle = entityManager.getEntityByID(attacker);
    if (auto attackerEntity = attackerHandle.lock())
    {
        auto data = attackerEntity->getComponentByType<RangeAttackData>();
        for (auto id : targets)
        {
            combat.dealDamageNow({attacker, id, data->agility});
        }
    }
}
