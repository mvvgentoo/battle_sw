#ifndef INAVIGATIONSERVICE_HPP
#define INAVIGATIONSERVICE_HPP

#include "IGameService.hpp"

#include <memory>

#include "Core/Entity/EntityHandle.hpp"

#include <list>

class World;
class INavigationTask;
class IMovementBehavior;


class NavigationService : public IGameService
{
public:
    enum class NavTaskStatus
    {
        Exists,
        NewAssigned,
        NoTask
    };


	NavigationService(std::shared_ptr<World> world, EntityHandle owner);
	~NavigationService();

    void addNavTask(std::unique_ptr<INavigationTask> navTask);
    NavTaskStatus setCurrentNavTask();
	bool hasCurrentNavTask();

    ITurnBehavior::TurnStatus update();

private:
	EntityHandle _owner;
	std::weak_ptr<World> _world;

    std::list<std::unique_ptr<INavigationTask>> _navTasks;
    std::unique_ptr<INavigationTask> _currentTask;
    std::shared_ptr<IMovementBehavior> _moveBehavior;

};

#endif	// INAVIGATIONSERVICE_HPP
