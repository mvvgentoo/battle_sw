#include "FightService.hpp"

#include "Core/World.hpp"
#include "Core/FightSystem/IAttackBehavior.hpp"

FightService::FightService(std::shared_ptr<World> world, EntityID owner) :
		_owner(owner),
		_world(world)
{}

FightService::~FightService() {}

void FightService::addAttackBehavior(std::shared_ptr<IAttackBehavior> behavior)
{
    _behaviors.push_back(std::move(behavior));

    std::sort(_behaviors.begin(), _behaviors.end(), [](const auto& a, const auto& b) {
                  return a->getPriority() > b->getPriority();
              });
}

ITurnBehavior::TurnStatus FightService::update()
{
    auto worldPtr = _world.lock();
    if (worldPtr == nullptr)
    {
        return ITurnBehavior::TurnStatus::INVALID;
    }

    for (const auto& behavior : _behaviors)
    {
        const auto& entityManager = worldPtr->getEntityManager();
        if (behavior == nullptr || !behavior->canBeActivated(entityManager, _owner))
        {
            continue;
        }

        if(auto targets = behavior->findTargets(entityManager, _owner); !targets.empty() )
        {
            behavior->execute(_owner, targets, worldPtr->getCombatSystem());
            return ITurnBehavior::TurnStatus::SUCCESS;
        }
    }

    return ITurnBehavior::TurnStatus::IDLE;
}

int FightService::getPriority()
{
    return _priority;
}

void FightService::setPriority(int priority)
{
    _priority = priority;
}
