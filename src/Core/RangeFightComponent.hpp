#ifndef RANGEFIGHTCOMPONENT_HPP
#define RANGEFIGHTCOMPONENT_HPP

#include "BaseTypes.hpp"
#include "IBaseComponent.hpp"
#include "IFightComponent.hpp"
#include "ITargetSelectorStrategy.hpp"

#include <memory>
#include <vector>

class World;

class RangeFightComponent : public IBaseComponent, public IFightComponent
{
public:
	RangeFightComponent(
		int minRange, int maxRange, int damageAmount, std::shared_ptr<ITargetSelectorStrategy> targetSelector);

	int getMinRange() const override
	{
		return _minRange;
	}

	int getMaxRange() const override
	{
		return _maxRange;
	}

	virtual bool canBeActivated() override
	{
		return true;
	}

	int getDamageAmount() const override
	{
		return _damageAmount;
	}

	const std::vector<DamageEffectPtr>& getDamageEffects() const override;

	std::vector<EntityID> findTargets(
		const Position& current, std::weak_ptr<World> world, std::set<EntityID> idsToExclude) const override;

private:
	int _minRange;
	int _maxRange;
	int _damageAmount;
	std::shared_ptr<ITargetSelectorStrategy> _targetSelectStrategy;
	std::vector<DamageEffectPtr> _damageEffects;
};

#endif	// RANGEFIGHTCOMPONENT_HPP
