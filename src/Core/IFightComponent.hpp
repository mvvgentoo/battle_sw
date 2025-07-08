#ifndef IFIGHTCOMPONENT_H
#define IFIGHTCOMPONENT_H

#include "BaseTypes.hpp"
#include "DamageEffect.hpp"

#include <memory>
#include <set>
#include <vector>

class World;

using DamageEffectPtr = std::shared_ptr<DamageEffect>;

class IFightComponent
{
public:
	virtual ~IFightComponent() = default;
	virtual int getDamageAmount() const = 0;
	virtual std::vector<EntityID> findTargets(
		const Position& current, std::weak_ptr<World> world, std::set<EntityID> idsToExclude) const
		= 0;
	virtual int getMinRange() const = 0;
	virtual int getMaxRange() const = 0;
	virtual const std::vector<DamageEffectPtr>& getDamageEffects() const = 0;
};

#endif	// IFIGHTCOMPONENT_H
