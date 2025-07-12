#include "NavigationTask.hpp"

#include "Core/World.hpp"

NavigationTask::NavigationTask(Position target, uint32_t reachDistance) :
		_target(target),
		_reachDistance(reachDistance)
{}

bool NavigationTask::isReached(const Position& current) const
{
	return Grid::chebyshevDistance(current, _target) < _reachDistance;
}
