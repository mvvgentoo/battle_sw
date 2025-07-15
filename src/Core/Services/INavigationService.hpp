#ifndef INAVIGATIONSERVICE_HPP
#define INAVIGATIONSERVICE_HPP

#include "Core/Entity/EntityHandle.hpp"
#include "IGameService.hpp"

#include <list>
#include <memory>

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

	constexpr static int DefaultPriority = 50;
	NavigationService(
		std::shared_ptr<IWorldContext> worldCtx,
		EntityHandle owner,
		std::unique_ptr<IMovementBehavior> moveBhv,
		int priority = DefaultPriority);
	~NavigationService();

	void addNavTask(std::unique_ptr<INavigationTask> navTask);
	NavTaskStatus setCurrentNavTask();
	bool hasCurrentNavTask();

	ITurnBehavior::TurnStatus update() override;

private:
	std::weak_ptr<IWorldContext> _worldContext;
	EntityHandle _owner;
	std::unique_ptr<IMovementBehavior> _moveBehavior;
	int _priority;

	std::list<std::unique_ptr<INavigationTask>> _navTasks;
	std::unique_ptr<INavigationTask> _currentTask;

public:
	int getPriority() const override;
	void setPriority(int priority) override;
};

#endif	// INAVIGATIONSERVICE_HPP
