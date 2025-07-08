#ifndef BHVACTION_HPP
#define BHVACTION_HPP

#include "EntityHandle.hpp"

#include <memory>

class Entity;

class IBhvAction
{
public:
	virtual ~IBhvAction() = default;
	virtual bool execute(EntityHandle entityHandle) = 0;
};

class MeleeAttackIfInRange : public IBhvAction
{
public:
	MeleeAttackIfInRange();
	bool execute(EntityHandle entityHandle) override;
};

class RangeAttackIfInRange : public IBhvAction
{
public:
	RangeAttackIfInRange();
	bool execute(EntityHandle entityHandle) override;
};

class NavigationAction : public IBhvAction
{
public:
	NavigationAction();
	bool execute(EntityHandle entityHandle) override;
};

#endif	// BHVACTION_HPP
