#ifndef INAVIGATIONSERVICE_HPP
#define INAVIGATIONSERVICE_HPP

#include "IGameService.hpp"

#include <memory>

//#include "NavigationTask.hpp"
#include "Core/Entity/EntityHandle.hpp"

#include <list>

class World;
class NavigationTask;

class NavigationService : public IGameService
{
public:
	NavigationService(std::shared_ptr<World> world, EntityHandle owner);
	~NavigationService();

	CellFlag getCellOccupyType() const;
	bool moveTo();
	void addNavTask(std::unique_ptr<NavigationTask> navTask);
	void setCurrentNavTask();
	bool hasCurrentNavTask();

	EntityHandle getOwnerID() const
	{
		return _owner;
	}

    ITurnBehavior::TurnStatus update();

private:
	EntityHandle _owner;
	std::weak_ptr<World> _world;

	std::list<std::unique_ptr<NavigationTask>> _navTasks;
	std::unique_ptr<NavigationTask> _currentTask;

	// IGameService interface

public:

};

#endif	// INAVIGATIONSERVICE_HPP
