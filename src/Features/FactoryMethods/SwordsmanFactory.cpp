#include "SwordsmanFactory.hpp"

#include <Core/Services/FightService.hpp>
#include <Core/Services/HealthService.hpp>
#include <Core/Services/INavigationService.hpp>
#include <Core/FightSystem/ITargetSelectorStrategy.hpp>
#include <Core/World/IWorldContext.hpp>

#include "Features/FightBehaviors/MeleeAttackBehavior.hpp"
#include "Features/DataComponents/MeleeAttackData.hpp"
#include "Core/DataComponents/MovementData.hpp"
#include "Features/FightBehaviors/MeleeAttackBehavior.hpp"
#include "Features/NavBehaviors/SimpleMovementBehavior.hpp"
#include "Core/World/EntityHelper.hpp"
#include <Core/DataComponents/HealthComponent.hpp>

SwordsmanFactory::SwordsmanFactory(int hp, int meleeRange, int damage) :
		_hp(hp),
		_meleeRange(meleeRange),
		_damage(damage)
{}

std::unique_ptr<Entity> SwordsmanFactory::create(std::shared_ptr<IWorldContext> worldContext, EntityID id, Position pos, const UnitParams& params) const
{
    const int maxSteps = 1;
	int hp = params.get("hp", _hp);
	int strength = params.get("strength", _damage);
	int meleeRange = params.get("meleeRange", _meleeRange);

    auto entity = std::make_unique<Entity>(id, pos);

    // Health Service
    auto healthData = std::make_shared<HealthComponent>(hp);
    auto healthSrv = std::make_shared<HealthService>(id, worldContext, healthData);

    entity->addComponent<HealthComponent>(healthData);
    entity->addService<HealthService>(healthSrv);

    // Fight Service
    auto targetSelector = std::make_shared<RandomTargetSelector>();
    auto meleeAttackData = std::make_shared<MeleeAttackData>(strength, meleeRange, targetSelector);

    auto fightSrv = std::make_shared<FightService>(worldContext, id);
    fightSrv->addAttackBehavior(std::make_unique<MeleeAttackBehavior>(meleeAttackData));

    entity->addComponent<MeleeAttackData>(meleeAttackData);
    entity->addService<FightService>(fightSrv);

    // Navigation Service
    auto movementData = std::make_shared<MovementData>(maxSteps);
    auto simpleMovementBhv = std::make_unique<SimpleMovementBehavior>(movementData);
    auto navSrv = std::make_shared<NavigationService>(worldContext, EntityHelper::createHandle(*worldContext,id), std::move(simpleMovementBhv));

    entity->addComponent<MovementData>(movementData);
    entity->addService<NavigationService>(navSrv);

    return entity;
}
