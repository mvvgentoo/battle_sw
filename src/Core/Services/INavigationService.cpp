#include "INavigationService.hpp"

#include "IO/Events/MarchEnded.hpp"
#include "MovementComponent.hpp"
#include "NavigationTask.hpp"
#include "OccupancyComponent.hpp"
#include "World.hpp"

NavigationService::NavigationService(std::shared_ptr<World> world, EntityHandle owner) :
		_world(world),
		_owner(owner)
{}

CellFlag NavigationService::getCellOccupyType() const
{
	auto occupancyComponent = getComponentByType<OccupancyComponent>();
	return occupancyComponent ? occupancyComponent->getFlag() : CellFlag::OCCUPY;
}

NavigationService::~NavigationService() = default;

bool NavigationService::moveTo()
{
	setCurrentNavTask();
	if (_currentTask == nullptr)
	{
		return false;
	}

	Entity* entity = _owner.lock();
	if (entity == nullptr)
	{
		return false;
	}

	Position current = entity->getPosition();
	const Position& target = _currentTask->getTarget();

	auto movementComponent = getComponentByType<MovementComponent>();
	if (movementComponent == nullptr)
	{
		return false;
	}

	bool wasSuccesful = movementComponent->executeNavigation(current, target, entity->getID());

	if (_currentTask->isReached(current))
	{
		if (auto worldPtr = _world.lock())
		{
			worldPtr->emit(
				sw::io::MarchEnded{_owner.getId(), static_cast<uint32_t>(current.x), static_cast<uint32_t>(current.y)});
		}
		_currentTask.reset();
	}

	return wasSuccesful;
}

void NavigationService::update()
{
	if (_currentTask == nullptr)
	{
		setCurrentNavTask();
	}
	moveTo();
}

void NavigationService::setCurrentNavTask()
{
	if (_currentTask || _navTasks.empty())
	{
		return;
	}

	_currentTask = std::move(_navTasks.front());
	_navTasks.pop_front();
}

bool NavigationService::hasCurrentNavTask()
{
	return _currentTask != nullptr;
}

void NavigationService::addNavTask(std::unique_ptr<NavigationTask> navTask)
{
	_navTasks.push_back(std::move(navTask));
}
