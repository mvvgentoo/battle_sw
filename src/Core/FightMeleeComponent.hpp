#ifndef FIGHTMELEECOMPONENT_H
#define FIGHTMELEECOMPONENT_H

#include "BaseTypes.hpp"
#include "DamageEffect.hpp"
#include "IBaseComponent.hpp"
#include "IFightComponent.hpp"
#include "ITargetSelectorStrategy.hpp"

#include <memory>
#include <vector>

class World;

class FightMeleeComponent : public IBaseComponent, public IFightComponent
{
public:
	using DamageEffectPtr = std::shared_ptr<DamageEffect>;

	FightMeleeComponent(int meleeRange, int damageAmount, std::shared_ptr<ITargetSelectorStrategy> targetSelector);

	virtual bool canBeActivated() override
	{
		return true;
	}

	int getDamageAmount() const override
	{
		return _damageAmount;
	}

	int getMinRange() const override
	{
		return 0;
	}

	int getMaxRange() const override
	{
		return _meleeRange;
	}

	int getMeleeRange() const
	{
		return _meleeRange;
	}

	const std::vector<DamageEffectPtr>& getDamageEffects() const override;

	std::vector<EntityID> findTargets(
		const Position& current, std::weak_ptr<World> world, std::set<EntityID> idsToExclude) const override;

private:
	int _meleeRange;
	int _damageAmount;
	std::shared_ptr<ITargetSelectorStrategy> _targetSelectStrategy;

	std::vector<DamageEffectPtr> _damageEffects;

	// IBaseComponent interface
};

#endif	// FIGHTMELEECOMPONENT_H
