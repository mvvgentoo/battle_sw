#ifndef FIGHTSERVICE_HPP
#define FIGHTSERVICE_HPP

#include "BaseTypes.hpp"
#include "EntityHandle.hpp"
#include "IFightComponent.hpp"
#include "IGameService.hpp"

#include <vector>

class World;

class FightService : public IGameService
{
public:
	FightService(std::shared_ptr<World> world, EntityID owner);
	virtual ~FightService();

	FightService(const FightService&) = delete;
	FightService(FightService&&) = delete;
	FightService& operator=(const FightService&) = delete;
	FightService& operator=(FightService&&) = delete;

	virtual void update() override;

	std::vector<EntityID> findMeleeTargets() const;
	std::vector<EntityID> findRangeTargets() const;
	bool MeleeAttack(std::vector<EntityID> targets);
	bool RangeAttack(std::vector<EntityID> targets);

	bool isTargetValid(EntityHandle target);

	int getMeleeRangeModified(int meleeRange) const;
	std::pair<int, int> getRangedRangeModified(int minRange, int maxRange) const;

private:
	EntityID _owner;
	std::weak_ptr<World> _world;

	std::vector<EntityID> findTargetsFrom(const std::shared_ptr<IFightComponent>& component) const;
};

#endif	// FIGHTSERVICE_HPP
