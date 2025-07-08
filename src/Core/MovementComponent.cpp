#include "MovementComponent.hpp"

#include "IO/Events/UnitMoved.hpp"
#include "World.hpp"

#include <limits>

MovementComponent::MovementComponent(std::shared_ptr<World> world, int maxSteps) :
		_world(world),
		_maxSteps(maxSteps)
{}

MovementComponent::~MovementComponent() {}

bool MovementComponent::executeNavigation(Position& current, const Position& target, EntityID id)
{
	if (current == target)
	{
		return false;
	}

	auto worldPtr = _world.lock();
	if (worldPtr == nullptr)
	{
		return false;
	}

	int steps = _maxSteps;
	const auto& navGrid = worldPtr->getGrid();

	for (int s = 0; s < steps; ++s)
	{
		Direction dir = computeStep(current, target);
		if (dir.x == 0 && dir.y == 0)
		{
			break;
		}

		Position next = {current.x + dir.x, current.y + dir.y};

		const static std::vector<Direction> directions
			= {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

		auto bestDistance = std::numeric_limits<uint32_t>::max();
		bool found = false;
		if (navGrid.isOccupied(next) || !navGrid.inBounds(next))
		{
			for (const Direction& d : directions)
			{
				Position candidate{current.x + d.x, current.y + d.y};

				if (navGrid.isOccupied(candidate) || !navGrid.inBounds(candidate))
				{
					continue;
				}

				auto dist = Grid::chebyshevDistance(candidate, target);
				if (dist < bestDistance)
				{
					next = candidate;
					bestDistance = dist;
					found = true;
				}
			}
		}

		if (!found)
		{
			return false;
		}

		Position newPos{next.x, next.y};
		worldPtr->updateEntityPosition(id, newPos);
		current = newPos;

		worldPtr->emit(sw::io::UnitMoved{id, static_cast<uint32_t>(current.x), static_cast<uint32_t>(current.y)});

		if (current == target)
		{
			return true;
		}
		break;
	}

	return true;
}
