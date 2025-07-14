#ifndef INAVIGATIONSERVICE_HPP
#define INAVIGATIONSERVICE_HPP

#include "IGameService.hpp"

#include <memory>

#include "Core/Entity/EntityHandle.hpp"

#include <list>

class IWorldContext;
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


    NavigationService(std::shared_ptr<IWorldContext> worldCtx, EntityHandle owner);
	~NavigationService();

    void addNavTask(std::unique_ptr<INavigationTask> navTask);
    NavTaskStatus setCurrentNavTask();
	bool hasCurrentNavTask();

    ITurnBehavior::TurnStatus update() override;

private:
	EntityHandle _owner;
    std::weak_ptr<IWorldContext> _worldContext;

    std::list<std::unique_ptr<INavigationTask>> _navTasks;
    std::unique_ptr<INavigationTask> _currentTask;
    std::shared_ptr<IMovementBehavior> _moveBehavior;
    int _priority = 50;


    // IGameService interface
public:
    int getPriority() override;
    void setPriority(int priority) override;
};

#endif	// INAVIGATIONSERVICE_HPP
