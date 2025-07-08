#ifndef SWORDSMANTURNBEHAVIOR_H
#define SWORDSMANTURNBEHAVIOR_H

#include <Core/DefaultTurnBehavior.hpp>

class SwordsmanTurnBehavior : public DefaultTurnBehavior
{
public:
	SwordsmanTurnBehavior();
	~SwordsmanTurnBehavior();
	TurnStatus makeTurn(std::weak_ptr<World> world, EntityID owner);
};

#endif	// SWORDSMANTURNBEHAVIOR_H
