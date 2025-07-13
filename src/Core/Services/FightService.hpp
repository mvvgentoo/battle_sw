#ifndef FIGHTSERVICE_HPP
#define FIGHTSERVICE_HPP

#include "Core/BaseTypes.hpp"
#include "Core/Entity/EntityHandle.hpp"
#include "IGameService.hpp"

#include <vector>

class World;
class IAttackBehavior;

class FightService : public IGameService
{
public:
	FightService(std::shared_ptr<World> world, EntityID owner);
	virtual ~FightService();

	FightService(const FightService&) = delete;
	FightService(FightService&&) = delete;
	FightService& operator=(const FightService&) = delete;
	FightService& operator=(FightService&&) = delete;

    void addAttackBehavior(std::shared_ptr<IAttackBehavior> behavior);

    virtual ITurnBehavior::TurnStatus update() override;

private:
	EntityID _owner;
	std::weak_ptr<World> _world;
    std::vector<std::shared_ptr<IAttackBehavior>> _behaviors;

    int _priority = 100;
    //std::vector<EntityID> findTargetsFrom(const std::shared_ptr<IFightComponent>& component) const;

    // IGameService interface
public:
    int getPriority() override;
    void setPriority(int priority) override;
};

#endif	// FIGHTSERVICE_HPP
