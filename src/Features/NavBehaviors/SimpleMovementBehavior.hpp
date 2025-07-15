#ifndef SIMPLEMOVEMENTBEHAVIOR_HPP
#define SIMPLEMOVEMENTBEHAVIOR_HPP

#include "Core/Navigation/IMovementBehavior.hpp"

#include <memory>

class IWorldContext;

class SimpleMovementBehavior : public IMovementBehavior
{
public:
	SimpleMovementBehavior();
	~SimpleMovementBehavior();

	MovementResult moveTo(Position current, const Position& target, EntityID id, IWorldContext& world) override;
};

#endif	// SIMPLEMOVEMENTBEHAVIOR_HPP
