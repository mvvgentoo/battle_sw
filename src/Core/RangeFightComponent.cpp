#include "RangeFightComponent.hpp"

#include "Entity.hpp"
#include "FightService.hpp"
#include "World.hpp"

RangeFightComponent::RangeFightComponent(
	int minRange, int maxRange, int damageAmount, std::shared_ptr<ITargetSelectorStrategy> targetSelector) :
		_minRange(minRange),
		_maxRange(maxRange),
		_damageAmount(damageAmount),
		_targetSelectStrategy(targetSelector)
{}

const std::vector<DamageEffectPtr>& RangeFightComponent::getDamageEffects() const
{
	return _damageEffects;
}

std::vector<EntityID> RangeFightComponent::findTargets(
	const Position& current, std::weak_ptr<World> world, std::set<EntityID> idsToExclude) const
{
	if (auto sharedWorld = world.lock())
	{
		// Check enemies near
		// TODO: optimize
		auto closeEnemies = sharedWorld->getNeighboursInRadius(
			current,
			[&idsToExclude](const std::unique_ptr<Entity>& entity, Position origin)
			{
				return entity && !idsToExclude.contains(entity->getID()) && entity->isAlive() && entity->canBeAttacked()
					   && Grid::chebyshevDistance(origin, entity->getPosition()) == 1;
			});

		if (!closeEnemies.empty())
		{
			return {};
		}

		auto candidates = sharedWorld->getNeighboursInRadius(
			current,
			[&idsToExclude, minRange = _minRange, maxRange = _maxRange](
				const std::unique_ptr<Entity>& entity, Position origin)
			{
				if (!entity || idsToExclude.contains(entity->getID()) || !entity->isAlive() || !entity->canBeAttacked())
				{
					return false;
				}

				int min = minRange;
				int max = maxRange;

				if (auto targetCmp = entity->getServiceByType<FightService>())
				{
					std::tie(min, max) = targetCmp->getRangedRangeModified(minRange, maxRange);
				}

				uint32_t dist = Grid::chebyshevDistance(origin, entity->getPosition());
				return dist >= static_cast<uint32_t>(min) && dist <= static_cast<uint32_t>(max);
			});

		return _targetSelectStrategy->selectTargets(candidates);
	}

	return {};
}
