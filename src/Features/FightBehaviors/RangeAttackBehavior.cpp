#include "RangeAttackBehavior.hpp"

#include "Core/Systems/EntityManager.hpp"

RangeAttackBehavior::RangeAttackBehavior(std::shared_ptr<RangeAttackData> data) :
		_data(std::move(data))
{}

int RangeAttackBehavior::getPriority() const
{
	return _data->priority;
}

bool RangeAttackBehavior::canBeActivated(const EntityManager&, EntityID) const
{
	return true;
}

std::vector<EntityID> RangeAttackBehavior::findTargets(const EntityManager& entityManager, EntityID self) const
{
	const Position& pos = entityManager.getEntityByID(self).lock()->getPosition();
	return _data->targetSelector->selectTargets(entityManager.getNeighboursInRadius(
		pos,
		[rMin = _data->rangeMin, rMax = _data->rangeMax, self](const auto& entity, Position pos)
		{
			auto dist = chebyshevDistance(pos, entity->getPosition());
			return entity && entity->isAlive() && entity->getID() != self && dist <= rMax && dist >= rMin;
		}));
}

void RangeAttackBehavior::execute(EntityID attacker, const std::vector<EntityID>& targets, CombatSystem& combat) const
{
	for (auto id : targets)
	{
		combat.dealDamageNow({attacker, id, _data->agility});
	}
}
