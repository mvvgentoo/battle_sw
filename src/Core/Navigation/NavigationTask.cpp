#include "NavigationTask.hpp"

#include "Core/Systems/NavGridSystem.hpp"

NavigationTask::NavigationTask(Position target, uint32_t reachDistance) :
		_target(target),
		_reachDistance(reachDistance)
{}

bool NavigationTask::isReached(const Position& current) const
{
    return NavGridSystem::chebyshevDistance(current, _target) < _reachDistance;
}
