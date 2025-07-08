#ifndef MOVEMENTCOMPONENT_HPP
#define MOVEMENTCOMPONENT_HPP

#include "BaseTypes.hpp"
#include "IBaseComponent.hpp"

#include <memory>

class World;

class MovementComponent : public IBaseComponent
{
public:
	struct Direction
	{
		int x, y;

		Direction(int x_, int y_) :
				x(x_),
				y(y_)
		{}
	};

	bool canBeActivated()
	{
		return true;
	}

	MovementComponent(std::shared_ptr<World> world, int maxSteps = 1);
	~MovementComponent();

	int getMaxStepsPerTurn() const
	{
		return _maxSteps;
	}

	bool executeNavigation(Position& current, const Position& target, EntityID id);

private:
	int _maxSteps;
	std::weak_ptr<World> _world;

	Direction computeStep(const Position& from, const Position& to) const
	{
		int dx = (int)to.x - (int)from.x;
		int dy = (int)to.y - (int)from.y;

		int stepX = dx == 0 ? 0 : dx / abs(dx);
		int stepY = dy == 0 ? 0 : dy / abs(dy);

		return {stepX, stepY};
	}
};

#endif	// MOVEMENTCOMPONENT_HPP
