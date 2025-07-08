#ifndef ITURNSTRATEGY_H
#define ITURNSTRATEGY_H

#include "BaseTypes.hpp"

#include <functional>
#include <memory>

class World;

class ITurnBehavior
{
public:
	enum class TurnStatus
	{
		SUCCESS,
		IDLE,
		INVALID
	};

	virtual TurnStatus makeTurn(std::weak_ptr<World> world, EntityID owner) = 0;
};

#endif	// ITURNSTRATEGY_H
