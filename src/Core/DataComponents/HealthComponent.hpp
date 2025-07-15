#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include "IDataComponent.hpp"

struct HealthComponent : public IDataComponent
{
	int hpMax = 10;
	int currentHP = 1;
	bool isDead = false;

	HealthComponent(int hpMax_, bool isDead_ = false) :
			hpMax(hpMax_),
			currentHP(hpMax_),
			isDead(isDead_)
	{}
};

#endif	// HEALTHCOMPONENT_HPP
