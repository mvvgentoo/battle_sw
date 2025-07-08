#include "FightService.hpp"

#include "FightMeleeComponent.hpp"
#include "HealthService.hpp"
#include "IO/Events/UnitAttacked.hpp"
#include "IRangeModifierVisitor.hpp"
#include "RangeFightComponent.hpp"
#include "World.hpp"

FightService::FightService(std::shared_ptr<World> world, EntityID owner) :
		_owner(owner),
		_world(world)
{}

FightService::~FightService() {}

void FightService::update() {}

std::vector<EntityID> FightService::findMeleeTargets() const
{
	auto&& meleeComponent = getComponentByType<FightMeleeComponent>();
	return findTargetsFrom(std::static_pointer_cast<IFightComponent>(meleeComponent));
}

std::vector<EntityID> FightService::findRangeTargets() const
{
	auto&& rangeComponent = getComponentByType<RangeFightComponent>();
	return findTargetsFrom(std::static_pointer_cast<IFightComponent>(rangeComponent));
}

bool FightService::MeleeAttack(std::vector<EntityID> targets)
{
	if (auto&& meleeComponent = getComponentByType<FightMeleeComponent>())
	{
		if (meleeComponent->canBeActivated())
		{
			auto sharedWorld = _world.lock();

			if (sharedWorld == nullptr)
			{
				return false;
			}

			for (auto id : targets)
			{
				auto entityToAttackHandle = sharedWorld->getEntityByID(id);
				if (auto entityToAttack = entityToAttackHandle.lock())
				{
					for (auto&& damageEffectPtr : meleeComponent->getDamageEffects())
					{
						damageEffectPtr->apply(id);
					}

					if (auto&& healthService = entityToAttack->getServiceByType<HealthService>())
					{
						auto targetHP = healthService->getCurrentHP();
						sharedWorld->emit(sw::io::UnitAttacked{
							_owner,
							id,
							static_cast<uint32_t>(meleeComponent->getDamageAmount()),
							static_cast<uint32_t>(targetHP)});
						healthService->applyDamage(meleeComponent->getDamageAmount());
					}
				}
			}

			return !targets.empty();
		}
	}

	return false;
}

bool FightService::RangeAttack(std::vector<EntityID> targets)
{
	if (auto&& rangeComponent = getComponentByType<RangeFightComponent>())
	{
		if (!rangeComponent->canBeActivated())
		{
			return false;
		}

		auto sharedWorld = _world.lock();
		if (sharedWorld == nullptr)
		{
			return false;
		}

		for (auto id : targets)
		{
			auto entityToAttackHandle = sharedWorld->getEntityByID(id);
			if (auto entityToAttack = entityToAttackHandle.lock())
			{
				for (auto&& damageEffectPtr : rangeComponent->getDamageEffects())
				{
					damageEffectPtr->apply(id);
				}

				if (auto&& healthService = entityToAttack->getServiceByType<HealthService>())
				{
					auto targetHP = healthService->getCurrentHP();
					sharedWorld->emit(sw::io::UnitAttacked{
						_owner,
						id,
						static_cast<uint32_t>(rangeComponent->getDamageAmount()),
						static_cast<uint32_t>(targetHP)});
					healthService->applyDamage(rangeComponent->getDamageAmount());
				}
			}
		}

		return !targets.empty();
	}

	return false;
}

bool FightService::isTargetValid(EntityHandle target)
{
	if (auto entity = target.lock())
	{
		return entity->canBeAttacked() && entity->isAlive();
	}

	return false;
}

int FightService::getMeleeRangeModified(int meleeRange) const
{
	RangeModifierCollector collector(meleeRange, 0, 0);

	for (const auto& component : findAllComponents<IRangeModifiable>())
	{
		if (component != nullptr)
		{
			component->accept(collector);
		}
	}

	return collector.meleeMax();
}

std::pair<int, int> FightService::getRangedRangeModified(int minRange, int maxRange) const
{
	RangeModifierCollector collector(0, minRange, maxRange);

	for (const auto& component : findAllComponents<IRangeModifiable>())
	{
		if (component != nullptr)
		{
			component->accept(collector);
		}
	}

	return {collector.rangedMin(), collector.rangedMax()};
}

std::vector<EntityID> FightService::FightService::findTargetsFrom(
	const std::shared_ptr<IFightComponent>& component) const
{
	if (!component)
	{
		return {};
	}

	auto sharedWorld = _world.lock();

	if (sharedWorld == nullptr)
	{
		return {};
	}

	auto&& attackerHandle = sharedWorld->getEntityByID(_owner);
	auto attacker = attackerHandle.lock();

	//assert(attacker != nullptr);
	if (!attacker)
	{
		return {};
	}

	return component->findTargets(attacker->getPosition(), _world, {attacker->getID()});
}
