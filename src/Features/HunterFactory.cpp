#include "HunterFactory.hpp"

#include <Core/Services/FightService.hpp>
#include <Core/Services/HealthService.hpp>
#include <Core/Services/INavigationService.hpp>
#include <Core/FightSystem/ITargetSelectorStrategy.hpp>

#include <Core/World/IWorldContext.hpp>

#include <Core/DataComponents/MeleeAttackData.hpp>
#include "Core/DataComponents/MovementData.hpp"
#include "Core/DataComponents/RangeAttackData.hpp"
#include "Core/FightSystem/MeleeAttackBehavior.hpp"
#include "Core/FightSystem/RangeAttackBehavior.hpp"
#include "Core/Navigation/SimpleMovementBehavior.hpp"
#include "Core/World/EntityHelper.hpp"

#include <Core/DataComponents/HealthComponent.hpp>

HunterFactory::HunterFactory(int hp, int minRange, int maxRange, int meleeRange, int agility, int strength) :
		_hp(hp),
		_minAttackRange(minRange),
		_maxAttackRange(maxRange),
		_meleeRange(meleeRange),
		_agility(agility),
		_strength(strength)
{}

std::unique_ptr<Entity> HunterFactory::create(std::shared_ptr<IWorldContext> worldContext, EntityID id, Position pos, const UnitParams& params) const
{
    if (worldContext == nullptr)
    {
        return nullptr;
    }

    const int maxSteps = 1;
	int hp = params.get("hp", _hp);
	int meleeRange = params.get("meleeRange", _meleeRange);
	int strength = params.get("strength", _strength);
	int minAttackRange = params.get("minRange", _minAttackRange);
	int maxAttackRange = params.get("maxRange", _maxAttackRange);
	int agility = params.get("agility", _agility);

    auto entity = std::make_unique<Entity>(id, pos);

    // Health Service
    auto healthData = std::make_shared<HealthComponent>(hp);
    auto healthSrv = std::make_shared<HealthService>(id, worldContext, healthData);

    entity->addComponent<HealthComponent>(healthData);
    entity->addService<HealthService>(healthSrv);

    // Fight Service
    auto targetSelector = std::make_shared<RandomTargetSelector>();
    auto meleeAttackData = std::make_shared<MeleeAttackData>(strength, meleeRange, targetSelector);
    auto rangeAttackData = std::make_shared<RangeAttackData>(agility, minAttackRange, maxAttackRange, targetSelector);

    auto fightSrv = std::make_shared<FightService>(worldContext, id);
    fightSrv->addAttackBehavior(std::make_unique<MeleeAttackBehavior>(meleeAttackData));
    fightSrv->addAttackBehavior(std::make_unique<RangeAttackBehavior>(rangeAttackData));

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
