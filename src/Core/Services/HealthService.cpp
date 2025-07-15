#include "HealthService.hpp"

#include "Core/DataComponents/HealthComponent.hpp"
#include "Core/Systems/EventManager.hpp"
#include "Core/World/IWorldContext.hpp"
#include "IO/Events/UnitDied.hpp"

HealthService::HealthService(
	EntityID owner, std::weak_ptr<IWorldContext> worldContext, std::shared_ptr<HealthComponent> healthData) :
		_owner(owner),
		_worldContext(worldContext),
		_healthData(healthData)
{}

HealthService::~HealthService() {}

HealthService::hp_amount HealthService::getCurrentHP() const
{
	return _healthData ? _healthData->currentHP : 0;
}

bool HealthService::isAlive() const
{
	return _healthData && !_healthData->isDead && _healthData->currentHP > 0;
}

bool HealthService::applyDamage(hp_amount amount)
{
	if (!isAlive())
	{
		return false;
	}

	_healthData->currentHP = std::max(0, _healthData->currentHP - amount);
	if (_healthData->currentHP == 0)
	{
		markDead();
	}
	return true;
}

bool HealthService::applyHeal(hp_amount amount)
{
	if (!isAlive())
	{
		return false;
	}

	_healthData->currentHP = std::min(_healthData->hpMax, _healthData->currentHP + amount);
	return true;
}

ITurnBehavior::TurnStatus HealthService::update()
{
	return ITurnBehavior::TurnStatus::IDLE;
}

void HealthService::markDead()
{
	if (_healthData && !_healthData->isDead)
	{
		_healthData->isDead = true;

		if (auto worldCtx = _worldContext.lock())
		{
			worldCtx->getEventManager().emit(sw::io::UnitDied{_owner});
		}
	}
}

int HealthService::getPriority() const
{
	return _priority;
}

void HealthService::setPriority(int priority)
{
	_priority = priority;
}
