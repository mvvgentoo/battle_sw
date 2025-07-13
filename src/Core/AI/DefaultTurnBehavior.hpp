#ifndef DEFAULTTURNBEHAVIOR_HPP
#define DEFAULTTURNBEHAVIOR_HPP

#include "ITurnBehaviour.hpp"


class DefaultTurnBehavior : public ITurnBehavior
{
public:
	DefaultTurnBehavior();
	virtual ~DefaultTurnBehavior();

	TurnStatus makeTurn(std::weak_ptr<World> world, EntityID owner) override;

private:

};

#endif	// DEFAULTTURNBEHAVIOR_HPP
