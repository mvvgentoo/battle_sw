#ifndef ITURNSTRATEGY_H
#define ITURNSTRATEGY_H

#include "Core/Utils/BaseTypes.hpp"

#include <functional>
#include <memory>

class IWorldContext;

class ITurnBehavior
{
public:
	enum class TurnStatus
	{
		SUCCESS,
		IDLE,
		INVALID
	};

    virtual TurnStatus makeTurn(std::weak_ptr<IWorldContext> worldCtx, EntityID owner) = 0;
};

#endif	// ITURNSTRATEGY_H
