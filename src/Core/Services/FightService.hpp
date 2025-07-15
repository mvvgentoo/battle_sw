#ifndef FIGHTSERVICE_HPP
#define FIGHTSERVICE_HPP

#include "Core/Utils/BaseTypes.hpp"
#include "IGameService.hpp"

#include <vector>

class IWorldContext;
class IAttackBehavior;

class FightService : public IGameService
{
public:
    constexpr static int DefaultPriority = 100;
    FightService(std::shared_ptr<IWorldContext> worldContext, EntityID owner, int priority = DefaultPriority);
	virtual ~FightService();

	FightService(const FightService&) = delete;
	FightService(FightService&&) = delete;
	FightService& operator=(const FightService&) = delete;
	FightService& operator=(FightService&&) = delete;

	void addAttackBehavior(std::shared_ptr<IAttackBehavior> behavior);

	virtual ITurnBehavior::TurnStatus update() override;

private:	
	std::weak_ptr<IWorldContext> _worldContext;
    EntityID _owner;
    int _priority;
    std::vector<std::shared_ptr<IAttackBehavior>> _behaviors;

public:
	int getPriority() const override;
	void setPriority(int priority) override;
};

#endif	// FIGHTSERVICE_HPP
