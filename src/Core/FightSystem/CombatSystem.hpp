#ifndef COMBATSYSTEM_HPP
#define COMBATSYSTEM_HPP

#include "Core/Utils/BaseTypes.hpp"

#include <memory>

class IWorldContext;

struct DamageEvent
{
	EntityID attacker;
	EntityID target;
	int damage;
};

class CombatSystem
{
public:
	CombatSystem();
	~CombatSystem();
	void dealDamageNow(const DamageEvent& evt, const IWorldContext& worldCtx) const;

private:
	std::weak_ptr<IWorldContext> _worldContext;
};

#endif	// COMBATSYSTEM_HPP
