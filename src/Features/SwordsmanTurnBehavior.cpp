#include "SwordsmanTurnBehavior.hpp"

#include <Core/BhvAction.hpp>
#include <Core/FightService.hpp>
#include <Core/INavigationService.hpp>
#include <Core/World.hpp>

SwordsmanTurnBehavior::SwordsmanTurnBehavior()
{
	addAction(std::make_unique<MeleeAttackIfInRange>());
	addAction(std::make_unique<NavigationAction>());
}

SwordsmanTurnBehavior::~SwordsmanTurnBehavior() {}

ITurnBehavior::TurnStatus SwordsmanTurnBehavior::makeTurn(std::weak_ptr<World> world, EntityID owner)
{
	return DefaultTurnBehavior::makeTurn(world, owner);
}
