#include "DefaultTurnBehavior.hpp"
#include "Core/Systems/EntityManager.hpp"
#include "Core/World/IWorldContext.hpp"
#include "Core/World/IWorldContext.hpp"
#include "Core/Services/IGameService.hpp"

DefaultTurnBehavior::DefaultTurnBehavior() {}

DefaultTurnBehavior::~DefaultTurnBehavior() {}

ITurnBehavior::TurnStatus DefaultTurnBehavior::makeTurn(std::weak_ptr<IWorldContext> worldCtx, EntityID owner)
{
    if (auto worldContext = worldCtx.lock())
	{
        auto entity = worldContext->getEntityManager().getEntityByID(owner);
		auto entityPtr = entity.lock();
		if (!entityPtr || !entityPtr->isAlive())
		{
			return TurnStatus::INVALID;
		}

        auto services = entityPtr->getAllServices();

        std::sort(services.begin(), services.end(), [](const auto& a, const auto& b) {
            return a->getPriority() > b->getPriority();
        });

        for (auto& service : services)
        {
            if (!service)
            {
                continue;
            }

            auto status = service->update();
            if (status == TurnStatus::SUCCESS)
            {
                return TurnStatus::SUCCESS;
            }
        }

        return TurnStatus::IDLE;
    }

    return TurnStatus::INVALID;
}
