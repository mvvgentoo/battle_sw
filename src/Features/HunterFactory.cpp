#include "HunterFactory.hpp"

#include "HunterTurnBehavior.hpp"

#include <Core/FightMeleeComponent.hpp>
#include <Core/FightService.hpp>
#include <Core/HealthService.hpp>
#include <Core/INavigationService.hpp>
#include <Core/ITargetSelectorStrategy.hpp>
#include <Core/MovementComponent.hpp>
#include <Core/RangeFightComponent.hpp>
#include <Core/World.hpp>

HunterFactory::HunterFactory(int hp, int minRange, int maxRange, int meleeRange, int agility, int strength) :
		_hp(hp),
		_minAttackRange(minRange),
		_maxAttackRange(maxRange),
		_meleeRange(meleeRange),
		_agility(agility),
		_strength(strength)
{}

std::unique_ptr<Entity> HunterFactory::create(
	std::shared_ptr<World> world, EntityID id, Position pos, const UnitParams& params) const
{
	int hp = params.get("hp", _hp);
	int meleeRange = params.get("meleeRange", _meleeRange);
	int strength = params.get("strength", _strength);
	int minAttackRange = params.get("minRange", _minAttackRange);
	int maxAttackRange = params.get("maxRange", _maxAttackRange);
	int agility = params.get("agility", _agility);

	auto entity = std::make_unique<Entity>(id, pos, std::make_unique<HunterTurnBehavior>());

	auto healthSrv = std::make_shared<HealthService>(hp, id, world);
	entity->addService<HealthService>(healthSrv);

	auto fightSrv = std::make_shared<FightService>(world, id);
	auto targetSelector = std::make_shared<RandomTargetSelector>();
	auto meleeComponent = std::make_shared<FightMeleeComponent>(meleeRange, strength, targetSelector);
	fightSrv->addComponent<FightMeleeComponent>(meleeComponent);
	auto rangeComponent
		= std::make_shared<RangeFightComponent>(minAttackRange, maxAttackRange, agility, targetSelector);
	fightSrv->addComponent<RangeFightComponent>(rangeComponent);

	entity->addService<FightService>(fightSrv);

	auto navSrv = std::make_shared<NavigationService>(world, world->getEntityByID(id));
	const int maxSteps = 1;
	auto movementComponent = std::make_shared<MovementComponent>(world, maxSteps);
	navSrv->addComponent<MovementComponent>(movementComponent);
	entity->addService<NavigationService>(navSrv);

	return entity;
}
