#ifndef DAMAGEEFFECT_HPP
#define DAMAGEEFFECT_HPP

#include "BaseTypes.hpp"

#include <string>

class DamageEffect
{
public:
	DamageEffect();
	virtual void apply(EntityID entityID) = 0;

private:
	std::string _type;
	int amount;
};

#endif	// DAMAGEEFFECT_HPP
