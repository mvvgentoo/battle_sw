#ifndef HUNTERTURNBEHAVIOR_H
#define HUNTERTURNBEHAVIOR_H

#include <Core/DefaultTurnBehavior.hpp>

class HunterTurnBehavior : public DefaultTurnBehavior
{
public:
	HunterTurnBehavior();
	~HunterTurnBehavior();
	TurnStatus makeTurn(std::weak_ptr<World> world, EntityID owner);
};

#endif	// SWORDSMANTURNBEHAVIOR_H
