#include "HealthService.hpp"

#include "Core/DataComponents/HealthComponent.hpp"
#include "Core/Systems/EventManager.hpp"
#include "Core/World/IWorldContext.hpp"
#include "IO/Events/UnitDied.hpp"
#include "Core/Systems/EntityManager.hpp"

HealthService::HealthService(std::weak_ptr<IWorldContext> worldContext,
    EntityID owner, int priority) :
        _worldContext(worldContext),
        _owner(owner),
        _priority(priority)
{
    if(auto ctx = worldContext.lock())
    {
        _handle = EntityHandle(ctx->getEntityManager().getSharedData(), _owner);
    }
}

HealthService::~HealthService() {}

HealthService::hp_amount HealthService::getCurrentHP() const
{
    if (auto entity = _handle.lock())
    {
        auto healthData = entity->getComponentByType<HealthComponent>();
        return healthData ? healthData->currentHP : 0;
    }

    return 0;
}

bool HealthService::isAlive() const
{
    if (auto entity = _handle.lock())
    {
        auto healthData = entity->getComponentByType<HealthComponent>();
        return healthData && !healthData->isDead && healthData->currentHP > 0;
    }

    return true;
}

static void markDead(HealthComponent* healthData, EntityID id, std::weak_ptr<IWorldContext> worldContext)
{
    if (healthData && !healthData->isDead)
    {
        healthData->isDead = true;

        if (auto worldCtx = worldContext.lock())
        {
            worldCtx->getEventManager().emit(sw::io::UnitDied{id});
        }
    }
}

bool HealthService::applyDamage(hp_amount amount)
{
	if (!isAlive())
	{
		return false;
	}

    if (auto entity = _handle.lock())
    {
        auto healthData = entity->getComponentByType<HealthComponent>();
        healthData->currentHP = std::max(0, healthData->currentHP - amount);
        if (healthData->currentHP == 0)
        {
            markDead(healthData.get(), _owner, _worldContext);
        }
        return true;
    }

    return false;
}

bool HealthService::applyHeal(hp_amount amount)
{
	if (!isAlive())
	{
		return false;
	}

    if (auto entity = _handle.lock())
    {
        auto healthData = entity->getComponentByType<HealthComponent>();
        healthData->currentHP = std::min(healthData->hpMax, healthData->currentHP + amount);

        return true;
    }

    return false;
}

ITurnBehavior::TurnStatus HealthService::update()
{
	return ITurnBehavior::TurnStatus::IDLE;
}

int HealthService::getPriority() const
{
	return _priority;
}

void HealthService::setPriority(int priority)
{
	_priority = priority;
}
