#include "RangeAttackBehavior.hpp"

#include "Core/FightSystem/CombatSystem.hpp"
#include "Core/Systems/EntityManager.hpp"
#include "Core/World/IWorldContext.hpp"
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

void RangeAttackBehavior::execute(const IWorldContext &worldContext, EntityID attacker, const std::vector<EntityID>& targets) const
{
    auto attackerHandle = worldContext.getEntityManager().getEntityByID(attacker);
    if (auto attackerEntity = attackerHandle.lock())
    {
        auto data = attackerEntity->getComponentByType<RangeAttackData>();
        for (auto id : targets)
        {
            worldContext.getCombatSystem().dealDamageNow({attacker, id, data->agility}, worldContext);
        }
    }
}
