#include "INavigationService.hpp"

#include "Core/Systems/EventManager.hpp"
#include "IO/Events/MarchEnded.hpp"
#include "Core/Navigation/IMovementBehavior.hpp"
#include "Core/Navigation/INavigationTask.hpp"
#include "Core/World/IWorldContext.hpp"
#include "IO/Events/MarchStarted.hpp"
#include "IO/Events/UnitMoved.hpp"

NavigationService::NavigationService(std::shared_ptr<IWorldContext> worldCtx, EntityHandle owner) :
        _worldContext(worldCtx),
		_owner(owner)
{}

NavigationService::~NavigationService() = default;

ITurnBehavior::TurnStatus NavigationService::update()
{
    auto worldCtx = _worldContext.lock();
    if (worldCtx == nullptr)
    {
        return ITurnBehavior::TurnStatus::INVALID;
    }

    auto navTaskStatus = setCurrentNavTask();

    if ( Entity* entity = _owner.lock() )
    {
        if (_moveBehavior != nullptr)
        {
            auto currentPos = entity->getPosition();
            auto targetPos = _currentTask->getTarget();

            if (navTaskStatus == NavTaskStatus::NewAssigned)
            {
                worldCtx->getEventManager().emit(sw::io::MarchStarted{_owner.getId(),
                                static_cast<uint32_t>(currentPos.x), static_cast<uint32_t>(currentPos.y),
                                static_cast<uint32_t>(targetPos.x), static_cast<uint32_t>(targetPos.y)}
                               );
            }

            auto result = _moveBehavior->moveTo(currentPos, targetPos, entity->getID(), *worldCtx);

            if (result.wasSuccesful)
            {
                worldCtx->getEventManager().emit(sw::io::UnitMoved{_owner.getId(), static_cast<uint32_t>(result.to.x), static_cast<uint32_t>(result.to.y)});
                if (result.targetReached || _currentTask->isReached(result.to) )
                {
                    worldCtx->getEventManager().emit(sw::io::MarchEnded{_owner.getId(), static_cast<uint32_t>(result.to.x), static_cast<uint32_t>(result.to.y)});
                    _currentTask.reset();
                }

                return ITurnBehavior::TurnStatus::SUCCESS;
            }
        }
    }

    return ITurnBehavior::TurnStatus::IDLE;
}

NavigationService::NavTaskStatus NavigationService::setCurrentNavTask()
{
    if (_currentTask )
    {
        return NavTaskStatus::Exists;
	}

    if (_navTasks.empty())
    {
        return NavTaskStatus::NoTask;
    }

	_currentTask = std::move(_navTasks.front());
	_navTasks.pop_front();
    return NavTaskStatus::NewAssigned;
}

bool NavigationService::hasCurrentNavTask()
{
	return _currentTask != nullptr;
}

void NavigationService::addNavTask(std::unique_ptr<INavigationTask> navTask)
{
	_navTasks.push_back(std::move(navTask));
}

int NavigationService::getPriority()
{
    return _priority;
}

void NavigationService::setPriority(int priority)
{
    _priority = priority;
}
