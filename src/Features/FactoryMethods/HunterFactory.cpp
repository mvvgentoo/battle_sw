#include "HunterFactory.hpp"

#include "Core/DataComponents/HealthComponent.hpp"
#include "Core/DataComponents/MovementData.hpp"
#include "Core/FightSystem/ITargetSelectorStrategy.hpp"
#include "Core/Services/FightService.hpp"
#include "Core/Services/HealthService.hpp"
#include "Core/Services/INavigationService.hpp"
#include "Core/World/EntityHelper.hpp"
#include "Core/World/IWorldContext.hpp"
#include "Features/DataComponents/MeleeAttackData.hpp"
#include "Features/DataComponents/RangeAttackData.hpp"
#include "Features/FightBehaviors/MeleeAttackBehavior.hpp"
#include "Features/FightBehaviors/RangeAttackBehavior.hpp"
#include "Features/NavBehaviors/SimpleMovementBehavior.hpp"

HunterFactory::HunterFactory(int hp, int minRange, int maxRange, int meleeRange, int agility, int strength) :
		_hp(hp),
		_minAttackRange(minRange),
		_maxAttackRange(maxRange),
		_meleeRange(meleeRange),
		_agility(agility),
		_strength(strength)
{}

std::unique_ptr<Entity> HunterFactory::create(
	std::shared_ptr<IWorldContext> worldContext, EntityID id, Position pos, const UnitParams& params) const
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

	// Data components
	auto healthData = std::make_shared<HealthComponent>(hp);
	auto targetSelector = std::make_shared<RandomTargetSelector>();
	auto meleeAttackData = std::make_shared<MeleeAttackData>(strength, meleeRange, targetSelector);
	auto rangeAttackData = std::make_shared<RangeAttackData>(agility, minAttackRange, maxAttackRange, targetSelector);
	auto movementData = std::make_shared<MovementData>(maxSteps);

	entity->addComponent<MeleeAttackData>(meleeAttackData);
	entity->addComponent<RangeAttackData>(rangeAttackData);
	entity->addComponent<HealthComponent>(healthData);
	entity->addComponent<MovementData>(movementData);

	// Health service
	auto healthSrv = std::make_shared<HealthService>(worldContext, id);

	// Fight Service
	auto fightSrv = std::make_shared<FightService>(worldContext, id);
	fightSrv->addAttackBehavior(std::make_unique<MeleeAttackBehavior>());
	fightSrv->addAttackBehavior(std::make_unique<RangeAttackBehavior>());

	// Navigation Service
	auto navSrv = std::make_shared<NavigationService>(
		worldContext, EntityHelper::createHandle(*worldContext, id), std::make_unique<SimpleMovementBehavior>());

	// Add Services
	entity->addService<FightService>(fightSrv);
	entity->addService<NavigationService>(navSrv);
	entity->addService<HealthService>(healthSrv);

	return entity;
}
