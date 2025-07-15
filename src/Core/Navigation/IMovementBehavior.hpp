#ifndef IMOVEMENTBEHAVIOR_HPP
#define IMOVEMENTBEHAVIOR_HPP

#include "Core/Utils/BaseTypes.hpp"

class IWorldContext;

class IMovementBehavior
{
public:
	struct MovementResult
	{
		bool wasSuccesful;
		bool targetReached;
		Position from;
		Position to;
	};

	virtual ~IMovementBehavior() = default;

	virtual MovementResult moveTo(Position current, const Position& target, EntityID id, IWorldContext& world) = 0;
};

#endif
