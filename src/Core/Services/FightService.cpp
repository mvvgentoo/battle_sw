#include "FightService.hpp"

#include "Core/FightSystem/IAttackBehavior.hpp"
#include "Core/World/IWorldContext.hpp"

FightService::FightService(std::shared_ptr<IWorldContext> worldContext, EntityID owner, int priority) :
        _worldContext(worldContext),
        _owner(owner),
        _priority(priority)
{}

FightService::~FightService() {}

void FightService::addAttackBehavior(std::shared_ptr<IAttackBehavior> behavior)
{
	_behaviors.push_back(std::move(behavior));

	std::sort(
		_behaviors.begin(),
		_behaviors.end(),
		[](const auto& a, const auto& b) { return a->getPriority() > b->getPriority(); });
}

ITurnBehavior::TurnStatus FightService::update()
{
	auto worldContext = _worldContext.lock();
	if (worldContext == nullptr)
	{
		return ITurnBehavior::TurnStatus::INVALID;
	}

	for (const auto& behavior : _behaviors)
	{
		const auto& entityManager = worldContext->getEntityManager();
		if (behavior == nullptr || !behavior->canBeActivated(entityManager, _owner))
		{
			continue;
		}

		if (auto targets = behavior->findTargets(entityManager, _owner); !targets.empty())
		{
			behavior->execute(*worldContext, _owner, targets);
			return ITurnBehavior::TurnStatus::SUCCESS;
		}
	}

	return ITurnBehavior::TurnStatus::IDLE;
}

int FightService::getPriority() const
{
	return _priority;
}

void FightService::setPriority(int priority)
{
	_priority = priority;
}
