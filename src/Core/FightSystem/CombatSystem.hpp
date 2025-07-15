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
	CombatSystem(std::shared_ptr<IWorldContext> worldCtx);
	~CombatSystem();

	void setContext(std::shared_ptr<IWorldContext> worldCtx);

	void dealDamageNow(const DamageEvent& evt);

private:
	std::weak_ptr<IWorldContext> _worldContext;
};

#endif	// COMBATSYSTEM_HPP
