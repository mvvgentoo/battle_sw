#include "DefaultTurnBehavior.hpp"

#include "BhvAction.hpp"
#include "World.hpp"

DefaultTurnBehavior::DefaultTurnBehavior() {}

DefaultTurnBehavior::~DefaultTurnBehavior() {}

void DefaultTurnBehavior::addAction(std::unique_ptr<IBhvAction> action)
{
	_actions.emplace_back(std::move(action));
}

ITurnBehavior::TurnStatus DefaultTurnBehavior::makeTurn(std::weak_ptr<World> world, EntityID owner)
{
	if (auto worldPtr = world.lock())
	{
		auto entity = worldPtr->getEntityByID(owner);
		auto entityPtr = entity.lock();
		if (!entityPtr || !entityPtr->isAlive())
		{
			return TurnStatus::INVALID;
		}

		for (const auto& action : _actions)
		{
			if (action->execute(entity))
			{
				return TurnStatus::SUCCESS;
			}
		}
	}

	return TurnStatus::IDLE;
}
