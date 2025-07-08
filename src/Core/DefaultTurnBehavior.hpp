#ifndef DEFAULTTURNBEHAVIOR_HPP
#define DEFAULTTURNBEHAVIOR_HPP

#include "ITurnBehaviour.hpp"

class IBhvAction;

class DefaultTurnBehavior : public ITurnBehavior
{
public:
	DefaultTurnBehavior();
	virtual ~DefaultTurnBehavior();

	void addAction(std::unique_ptr<IBhvAction> action);
	TurnStatus makeTurn(std::weak_ptr<World> world, EntityID owner) override;

private:
	std::vector<std::unique_ptr<IBhvAction>> _actions;
};

#endif	// DEFAULTTURNBEHAVIOR_HPP
