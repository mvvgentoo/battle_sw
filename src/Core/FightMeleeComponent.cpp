#include "FightMeleeComponent.hpp"

#include "World.hpp"
//#include "ITargetSelectorStrategy.hpp"
#include "FightService.hpp"

FightMeleeComponent::FightMeleeComponent(
	int meleeRange, int damageAmount, std::shared_ptr<ITargetSelectorStrategy> targetSelector) :
		_meleeRange(meleeRange),
		_damageAmount(damageAmount),
		_targetSelectStrategy(targetSelector)
{}

const std::vector<FightMeleeComponent::DamageEffectPtr>& FightMeleeComponent::getDamageEffects() const
{
	return _damageEffects;
}

std::vector<EntityID> FightMeleeComponent::findTargets(
	const Position& current, std::weak_ptr<World> world, std::set<EntityID> idsToExclude) const
{
	if (auto sharedWorld = world.lock())
	{
		int range = getMeleeRange();
		auto result = sharedWorld->getNeighboursInRadius(
			current,
			[range, &idsToExclude](const std::unique_ptr<Entity>& entity, Position current)
			{
				if (entity == nullptr)
				{
					return false;
				}

				if (idsToExclude.contains(entity->getID()))
				{
					return false;
				}

				if (!entity->canBeAttacked() || !entity->isAlive())
				{
					return false;
				}

				int modifiedRange = range;
				if (auto targetCmp = entity->getServiceByType<FightService>())
				{
					modifiedRange = targetCmp->getMeleeRangeModified(modifiedRange);
				}

				return Grid::chebyshevDistance(current, entity->getPosition()) <= modifiedRange;
			});

		return _targetSelectStrategy->selectTargets(result);
	}

	return {};
}
