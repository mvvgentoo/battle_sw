#ifndef DEFAULTTURNBEHAVIOR_HPP
#define DEFAULTTURNBEHAVIOR_HPP

#include "ITurnBehaviour.hpp"

class IWorldContext;

class DefaultTurnBehavior : public ITurnBehavior
{
public:
	DefaultTurnBehavior();
	virtual ~DefaultTurnBehavior();

    TurnStatus makeTurn(std::weak_ptr<IWorldContext> worldCtx, EntityID owner) override;

private:

};

#endif	// DEFAULTTURNBEHAVIOR_HPP
