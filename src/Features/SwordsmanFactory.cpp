#include "SwordsmanFactory.hpp"

#include "SwordsmanTurnBehavior.hpp"

#include <Core/FightMeleeComponent.hpp>
#include <Core/FightService.hpp>
#include <Core/HealthService.hpp>
#include <Core/INavigationService.hpp>
#include <Core/ITargetSelectorStrategy.hpp>
#include <Core/MovementComponent.hpp>
#include <Core/World.hpp>

SwordsmanFactory::SwordsmanFactory(int hp, int meleeRange, int damage) :
		_hp(hp),
		_meleeRange(meleeRange),
		_damage(damage)
{}

std::unique_ptr<Entity> SwordsmanFactory::create(
	std::shared_ptr<World> world, EntityID id, Position pos, const UnitParams& params) const
{
	int hp = params.get("hp", _hp);
	int strength = params.get("strength", _damage);
	int meleeRange = params.get("meleeRange", _meleeRange);

	auto entity = std::make_unique<Entity>(id, pos, std::make_unique<SwordsmanTurnBehavior>());

	auto healthSrv = std::make_shared<HealthService>(hp, id, world);
	entity->addService<HealthService>(healthSrv);

	auto fightSrv = std::make_shared<FightService>(world, id);
	auto targetSelector = std::make_shared<RandomTargetSelector>();
	auto meleeComponent = std::make_shared<FightMeleeComponent>(meleeRange, strength, targetSelector);
	fightSrv->addComponent<FightMeleeComponent>(meleeComponent);

	entity->addService<FightService>(fightSrv);

	auto navSrv = std::make_shared<NavigationService>(world, world->getEntityByID(id));
	const int maxSteps = 1;
	auto movementComponent = std::make_shared<MovementComponent>(world, maxSteps);
	navSrv->addComponent<MovementComponent>(movementComponent);
	entity->addService<NavigationService>(navSrv);

	return entity;
}
