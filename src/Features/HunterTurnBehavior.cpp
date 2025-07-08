#include "HunterTurnBehavior.hpp"

#include <Core/BhvAction.hpp>
#include <Core/FightService.hpp>
#include <Core/INavigationService.hpp>
#include <Core/World.hpp>

HunterTurnBehavior::HunterTurnBehavior()
{
	addAction(std::make_unique<RangeAttackIfInRange>());
	addAction(std::make_unique<MeleeAttackIfInRange>());
	addAction(std::make_unique<NavigationAction>());
}

HunterTurnBehavior::~HunterTurnBehavior() {}

ITurnBehavior::TurnStatus HunterTurnBehavior::makeTurn(std::weak_ptr<World> world, EntityID owner)
{
	return DefaultTurnBehavior::makeTurn(world, owner);
}
