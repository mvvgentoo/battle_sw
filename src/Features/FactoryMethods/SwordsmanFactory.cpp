#include "SwordsmanFactory.hpp"

#include "Core/DataComponents/MovementData.hpp"
#include "Core/World/EntityHelper.hpp"
#include "Features/DataComponents/MeleeAttackData.hpp"
#include "Features/FightBehaviors/MeleeAttackBehavior.hpp"
#include "Features/NavBehaviors/SimpleMovementBehavior.hpp"

#include <Core/DataComponents/HealthComponent.hpp>
#include <Core/FightSystem/ITargetSelectorStrategy.hpp>
#include <Core/Services/FightService.hpp>
#include <Core/Services/HealthService.hpp>
#include <Core/Services/INavigationService.hpp>
#include <Core/World/IWorldContext.hpp>

SwordsmanFactory::SwordsmanFactory(int hp, int meleeRange, int damage) :
		_hp(hp),
		_meleeRange(meleeRange),
		_damage(damage)
{}

std::unique_ptr<Entity> SwordsmanFactory::create(
	std::shared_ptr<IWorldContext> worldContext, EntityID id, Position pos, const UnitParams& params) const
{
	const int maxSteps = 1;
	int hp = params.get("hp", _hp);
	int strength = params.get("strength", _damage);
	int meleeRange = params.get("meleeRange", _meleeRange);

	auto entity = std::make_unique<Entity>(id, pos);

	// Health Service
	auto healthData = std::make_shared<HealthComponent>(hp);
    auto movementData = std::make_shared<MovementData>(maxSteps);
    auto targetSelector = std::make_shared<RandomTargetSelector>();
    auto meleeAttackData = std::make_shared<MeleeAttackData>(strength, meleeRange, targetSelector);

    entity->addComponent<MovementData>(movementData);
    entity->addComponent<HealthComponent>(healthData);
    entity->addComponent<MeleeAttackData>(meleeAttackData);

	// Fight Service
	auto fightSrv = std::make_shared<FightService>(worldContext, id);
    fightSrv->addAttackBehavior(std::make_unique<MeleeAttackBehavior>());

    // Health Service
    auto healthSrv = std::make_shared<HealthService>(worldContext, id);

	// Navigation Service    
	auto navSrv = std::make_shared<NavigationService>(
        worldContext, EntityHelper::createHandle(*worldContext, id), std::make_unique<SimpleMovementBehavior>());

    // Add services
    entity->addService<NavigationService>(navSrv);
    entity->addService<FightService>(fightSrv);
    entity->addService<HealthService>(healthSrv);

	return entity;
}
