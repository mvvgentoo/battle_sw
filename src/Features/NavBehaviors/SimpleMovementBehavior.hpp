#ifndef SIMPLEMOVEMENTBEHAVIOR_HPP
#define SIMPLEMOVEMENTBEHAVIOR_HPP

#include "Core/Navigation/IMovementBehavior.hpp"

#include <memory>

class IWorldContext;
struct MovementData;

class SimpleMovementBehavior : public IMovementBehavior
{
public:
	explicit SimpleMovementBehavior(std::shared_ptr<MovementData> _data);
	~SimpleMovementBehavior();

	MovementResult moveTo(Position current, const Position& target, EntityID id, IWorldContext& world) override;

private:
	std::shared_ptr<MovementData> _data;
};

#endif	// SIMPLEMOVEMENTBEHAVIOR_HPP
