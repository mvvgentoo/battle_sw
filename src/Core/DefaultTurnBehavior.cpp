#include "DefaultTurnBehavior.hpp"

#include "World.hpp"

DefaultTurnBehavior::DefaultTurnBehavior() {}

DefaultTurnBehavior::~DefaultTurnBehavior() {}

ITurnBehavior::TurnStatus DefaultTurnBehavior::makeTurn(std::weak_ptr<World> world, EntityID owner)
{
	if (auto worldPtr = world.lock())
	{
        auto entity = worldPtr->getEntityManager().getEntityByID(owner);
		auto entityPtr = entity.lock();
		if (!entityPtr || !entityPtr->isAlive())
		{
			return TurnStatus::INVALID;
		}

	}

	return TurnStatus::IDLE;
}
